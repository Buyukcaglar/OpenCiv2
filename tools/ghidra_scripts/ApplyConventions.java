// Applies calling conventions from re/conventions.tsv (computed by
// tools/conventions.py) so the decompiler passes `this` in ECX correctly and
// knows which functions pop their own arguments.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;

public class ApplyConventions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String path = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work/re/conventions.tsv";
        BufferedReader r = new BufferedReader(new FileReader(path));
        String line = r.readLine(); // header
        int n = 0;
        FunctionManager fm = currentProgram.getFunctionManager();
        while ((line = r.readLine()) != null) {
            String[] f = line.split("\t", -1);
            Address a = toAddr(Long.parseLong(f[0], 16));
            Function fn = fm.getFunctionAt(a);
            if (fn == null) continue;
            if (!f[3].isEmpty()) continue; // non-standard register inputs: leave to manual work
            fn.setCallingConvention(f[1]);
            n++;
        }
        r.close();
        println("applied conventions to " + n + " functions");
    }
}
