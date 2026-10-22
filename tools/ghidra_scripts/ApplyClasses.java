// Puts each recovered class's methods into a Ghidra class namespace named
// after its struct (src/include/civ2classes.h, parsed by ApplyTypes), so the
// decompiler types `this` as that struct and prints this->field_N.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.*;

public class ApplyClasses extends GhidraScript {
    @Override
    public void run() throws Exception {
        String root = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work";
        SymbolTable st = currentProgram.getSymbolTable();
        int nc = 0, nm = 0;
        // Start from scratch: methods back to the global namespace, old classes removed.
        for (Function fn : currentProgram.getFunctionManager().getFunctions(true))
            if (fn.getParentNamespace().getName().matches("C_[0-9a-f]{8}(_[0-9a-f]+)?"))
                fn.setParentNamespace(currentProgram.getGlobalNamespace());
        List<Symbol> olds = new ArrayList<>();
        for (Symbol s : st.getDefinedSymbols())
            if (s.getSymbolType() == SymbolType.CLASS && s.getName().matches("C_[0-9a-f]{8}(_[0-9a-f]+)?")) olds.add(s);
        for (Symbol s : olds) s.delete();
        for (String line : Files.readAllLines(Paths.get(root, "re/classes.tsv"))) {
            if (line.startsWith("class")) continue;
            String[] f = line.split("\t");
            GhidraClass cls = st.getNamespace(f[0], currentProgram.getGlobalNamespace()) instanceof GhidraClass
                ? (GhidraClass) st.getNamespace(f[0], currentProgram.getGlobalNamespace())
                : st.createClass(currentProgram.getGlobalNamespace(), f[0], SourceType.ANALYSIS);
            nc++;
            for (String a : f[1].split(",")) {
                Function fn = getFunctionAt(toAddr(Long.parseLong(a, 16)));
                if (fn != null && !fn.isThunk()) { fn.setParentNamespace(cls); nm++; }
            }
        }
        println("classes " + nc + ", methods " + nm);
    }
}
