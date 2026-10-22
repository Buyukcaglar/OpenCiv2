// Gives functions that share a name (static helpers in different C runtime
// objects, e.g. wcsncnt) unique names NAME_ADDR, so calls resolve by name.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.util.*;

public class UniqueNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        Map<String, List<Function>> byName = new HashMap<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true))
            if (!f.isThunk()) byName.computeIfAbsent(f.getName(), k -> new ArrayList<>()).add(f);
        int n = 0;
        for (List<Function> fs : byName.values()) {
            if (fs.size() < 2) continue;
            for (Function f : fs) {
                f.setName(String.format("%s_%08x", f.getName(), f.getEntryPoint().getOffset()), SourceType.ANALYSIS);
                n++;
            }
        }
        println("renamed " + n + " functions with shared names");
    }
}
