// Exports the function table, thunk map, call graph, and decompiled C for
// every non-thunk function into the directory given as the first argument.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.util.*;

public class ExportAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work/re";
        FunctionManager fm = currentProgram.getFunctionManager();
        PrintWriter funcs = new PrintWriter(new FileWriter(outDir + "/functions.tsv"));
        PrintWriter calls = new PrintWriter(new FileWriter(outDir + "/calls.tsv"));
        funcs.println("entry\tsize\tname\tcc\tnparams\tpurge\tthunk_target\tsignature");
        for (Function f : fm.getFunctions(true)) {
            Function t = f.isThunk() ? f.getThunkedFunction(true) : null;
            funcs.printf("%s\t%d\t%s\t%s\t%d\t%d\t%s\t%s\n", f.getEntryPoint(), f.getBody().getNumAddresses(),
                f.getName(), f.getCallingConventionName(), f.getParameterCount(), f.getStackPurgeSize(),
                t == null ? "" : t.getEntryPoint().toString(), f.getSignature().getPrototypeString());
            if (t == null)
                for (Function c : f.getCalledFunctions(monitor)) calls.printf("%s\t%s\n", f.getEntryPoint(), c.getEntryPoint());
        }
        funcs.close(); calls.close();
        if (getScriptArgs().length > 1 && getScriptArgs()[1].equals("nodecomp")) return;
        DecompInterface ifc = new DecompInterface();
        ifc.toggleCCode(true); ifc.toggleSyntaxTree(true);
        ifc.openProgram(currentProgram);
        PrintWriter c = new PrintWriter(new BufferedWriter(new FileWriter(outDir + "/decomp.c")));
        int n = 0;
        for (Function f : fm.getFunctions(true)) {
            if (monitor.isCancelled()) break;
            if (f.isThunk()) continue;
            c.printf("\n// ==== FUNCTION %s %s\n", f.getEntryPoint(), f.getName());
            try {
                DecompileResults r = ifc.decompileFunction(f, 60, monitor);
                if (r != null && r.decompileCompleted()) {
                    // Global symbols as the decompiler typed them in this function.
                    HighFunction hf = r.getHighFunction();
                    Iterator<HighSymbol> it = hf.getGlobalSymbolMap().getSymbols();
                    while (it.hasNext()) {
                        HighSymbol hs = it.next();
                        String addr = hs.getStorage().isMemoryStorage() ? hs.getStorage().getMinAddress().toString() : "?";
                        c.printf("// GLOBAL %s\t%s\t%s\t%d\n", hs.getName(), addr, hs.getDataType().getDisplayName(), hs.getSize());
                    }
                    c.print(r.getDecompiledFunction().getC());
                }
                else c.printf("// decompile failed: %s\n", r == null ? "null" : r.getErrorMessage());
            } catch (Exception e) { c.printf("// exception %s\n", e); }
            if (++n % 200 == 0) { c.flush(); println("decompiled " + n); }
        }
        c.close();
        ifc.dispose();
        println("done " + n);
    }
}
