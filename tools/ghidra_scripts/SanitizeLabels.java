// Renames data labels whose names are not valid C identifiers (Ghidra names
// string labels after their contents, e.g. "s_PLAYCDTRACK_(%d)_00632fd4").
import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.*;

public class SanitizeLabels extends GhidraScript {
    @Override
    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        int n = 0;
        for (Symbol s : st.getAllSymbols(false)) {
            if (s.getSymbolType() != SymbolType.LABEL) continue;
            String name = s.getName();
            if (name.matches("[A-Za-z_][A-Za-z0-9_]*")) continue;
            String clean = name.replaceAll("[^A-Za-z0-9_]", "_");
            try { s.setName(clean, SourceType.USER_DEFINED); n++; } catch (Exception e) { }
        }
        println("sanitized " + n + " labels");
    }
}
