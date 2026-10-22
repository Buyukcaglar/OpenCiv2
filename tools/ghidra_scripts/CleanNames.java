// Removes false-positive library (FID/demangler) names from game code so every
// game function is named FUN_<addr> until we name it ourselves, and resets
// any signature FID attached to them.  CRT functions (>= CRT_START) keep their
// names, except ambiguous "FID_conflict:" ones which get address names.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.util.*;

public class CleanNames extends GhidraScript {
    static final long CRT_START = 0x5f1b80L;

    @Override
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        int n = 0;
        for (Function f : fm.getFunctions(true)) {
            if (f.isThunk()) continue;
            String name = f.getName();
            if (name.startsWith("FUN_")) continue;
            long a = f.getEntryPoint().getOffset();
            boolean junk = a < CRT_START || name.startsWith("FID_conflict") || name.startsWith("$") || name.contains("`");
            if (!junk) continue;
            if (f.getParentNamespace() != null && !f.getParentNamespace().isGlobal())
                f.setParentNamespace(currentProgram.getGlobalNamespace());
            f.setName(String.format("FUN_%08x", a), SourceType.ANALYSIS);
            f.replaceParameters(new ArrayList<Variable>(), Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, true, SourceType.DEFAULT);
            f.setReturnType(DataType.DEFAULT, SourceType.DEFAULT);
            f.setSignatureSource(SourceType.DEFAULT);
            n++;
        }
        println("cleaned " + n + " function names");
    }
}
