// Applies the reconstruction's types and names to the Ghidra project:
//   src/include/civ2types.h  -> data types (parsed with Ghidra's C parser)
//   re/symbols.tsv           -> names and types of globals (data), names of
//                               globals (var) and of functions (func)
// The decompiler then prints field accesses (units[i].owner) instead of raw
// address arithmetic, and the generator emits real declarations.
import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParser;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class ApplyTypes extends GhidraScript {
    DataTypeManager dtm;

    DataType resolveType(String spec) throws Exception {
        spec = spec.trim();
        int lb = spec.indexOf('[');
        if (lb >= 0) {
            DataType base = resolveType(spec.substring(0, lb));
            String dims = spec.substring(lb);
            List<Integer> ns = new ArrayList<>();
            for (String d : dims.replace("]", "").split("\\[")) if (!d.isEmpty()) ns.add(Integer.decode(d));
            DataType t = base;
            for (int i = ns.size() - 1; i >= 0; i--) t = new ArrayDataType(t, ns.get(i), t.getLength());
            return t;
        }
        if (spec.endsWith("*")) return new PointerDataType(resolveType(spec.substring(0, spec.length() - 1)));
        List<DataType> found = new ArrayList<>();
        dtm.findDataTypes(spec, found);
        if (found.isEmpty()) {
            BuiltInDataTypeManager b = BuiltInDataTypeManager.getDataTypeManager();
            b.findDataTypes(spec, found);
        }
        if (found.isEmpty()) throw new Exception("unknown type " + spec);
        return found.get(0);
    }

    @Override
    public void run() throws Exception {
        String root = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work";
        dtm = currentProgram.getDataTypeManager();
        // The parser has no preprocessor: drop directives (the header only uses
        // an include guard) except #pragma pack, which it understands.
        StringBuilder sb = new StringBuilder();
        for (String hdr : new String[] {"src/include/civ2types.h", "src/include/civ2classes.h"}) {
            if (!Files.exists(Paths.get(root, hdr))) continue;
            for (String l : Files.readAllLines(Paths.get(root, hdr))) {
                String t = l.trim();
                sb.append(t.startsWith("#") && !t.startsWith("#pragma pack") ? "" : l).append('\n');
            }
        }
        String header = sb.toString();
        // Class structs are regenerated each run: drop the previous ones.
        List<DataType> stale = new ArrayList<>();
        Iterator<DataType> all = dtm.getAllDataTypes();
        while (all.hasNext()) {
            DataType d = all.next();
            if (d instanceof Structure && d.getName().matches("C_[0-9a-f]{8}.*")) stale.add(d);
        }
        for (DataType d : stale) dtm.remove(d, monitor);
        CParser parser = new CParser(dtm, true, null);
        parser.parse(new ByteArrayInputStream(header.getBytes()));
        println("parsed types: " + parser.getComposites().size() + " composites, " + parser.getTypes().size() + " typedefs");

        Listing listing = currentProgram.getListing();
        SymbolTable st = currentProgram.getSymbolTable();
        int nd = 0, nf = 0;
        for (String line : Files.readAllLines(Paths.get(root, "re/symbols.tsv"))) {
            if (line.startsWith("addr") || line.startsWith("#") || line.trim().isEmpty()) continue;
            String[] f = line.split("\t");
            Address a = toAddr(Long.parseLong(f[0], 16));
            String kind = f[1], name = f[2];
            if (kind.equals("func")) {
                Function fn = getFunctionAt(a);
                if (fn != null) { fn.setName(name, SourceType.USER_DEFINED); nf++; }
                continue;
            }
            if (kind.equals("var")) {
                // a name only: the data keeps the type Ghidra gave it
                createLabel(a, name, true, SourceType.USER_DEFINED);
                nd++;
                continue;
            }
            DataType dt = resolveType(f[3]);
            Address end = a.add(dt.getLength() - 1);
            listing.clearCodeUnits(a, end, false);
            listing.createData(a, dt);
            // Drop auto labels inside the range so references print as fields.
            List<Symbol> old = new ArrayList<>();
            for (Symbol s : st.getSymbols(new AddressSet(a, end), SymbolType.LABEL, true)) old.add(s);
            for (Symbol s : old) if (!s.getName().equals(name)) s.delete();
            createLabel(a, name, true, SourceType.USER_DEFINED);
            nd++;
        }
        println("applied " + nd + " globals, " + nf + " function names");
    }
}
