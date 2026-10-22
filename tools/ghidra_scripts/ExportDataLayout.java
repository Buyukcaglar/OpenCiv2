// Exports the layout of the game's static data for generating src/data/:
//   re/data_items.tsv  every defined data item in .rdata/.data: addr len type name
//   re/data_refs.tsv   every data address referenced from code: addr  (count)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ExportDataLayout extends GhidraScript {
    @Override
    public void run() throws Exception {
        String root = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work";
        Memory mem = currentProgram.getMemory();
        AddressSet data = new AddressSet();
        for (MemoryBlock b : mem.getBlocks())
            if (b.getName().equals(".rdata") || b.getName().equals(".data")) data.add(b.getStart(), b.getEnd());

        PrintWriter w = new PrintWriter(new FileWriter(root + "/re/data_items.tsv"));
        w.println("addr\tlen\ttype\tname");
        DataIterator it = currentProgram.getListing().getDefinedData(data, true);
        while (it.hasNext()) {
            Data d = it.next();
            Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(d.getAddress());
            w.printf("%s\t%d\t%s\t%s\n", d.getAddress(), d.getLength(), d.getDataType().getDisplayName(),
                s == null ? "" : s.getName());
        }
        w.close();

        Map<Address, Integer> refs = new TreeMap<>();
        ReferenceManager rm = currentProgram.getReferenceManager();
        for (AddressRange r : data) {
            for (Address a = r.getMinAddress(); a.compareTo(r.getMaxAddress()) <= 0; a = a.next()) {
                int n = 0;
                for (Reference ref : rm.getReferencesTo(a))
                    if (getInstructionAt(ref.getFromAddress()) != null) n++;
                if (n > 0) refs.put(a, n);
                if (a.equals(r.getMaxAddress())) break;
            }
        }
        PrintWriter rw = new PrintWriter(new FileWriter(root + "/re/data_refs.tsv"));
        rw.println("addr\tcount");
        for (Map.Entry<Address, Integer> e : refs.entrySet()) rw.printf("%s\t%d\n", e.getKey(), e.getValue());
        rw.close();
        println("data items exported; referenced addresses: " + refs.size());
    }
}
