// Create functions at the given addresses (args) and decompile them into args[0] file.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import java.io.*;

public class MakeFuncs extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        PrintWriter out = new PrintWriter(new FileWriter(a[0]));
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        for (int i = 1; i < a.length; i++) {
            Address ad = toAddr(a[i]);
            new DisassembleCommand(ad, null, true).applyTo(currentProgram, monitor);
            Function f = getFunctionAt(ad);
            if (f == null) f = createFunction(ad, null);
            if (f == null) { out.println("// failed " + a[i]); continue; }
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            out.printf("\n// ==== FUNCTION %s %s\n", f.getEntryPoint(), f.getName());
            if (r != null && r.decompileCompleted()) out.print(r.getDecompiledFunction().getC());
            else out.println("// decompile failed");
        }
        out.close();
    }
}
