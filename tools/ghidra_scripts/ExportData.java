// Exports every symbol/defined datum in non-code blocks with its data type,
// so the C generator can declare globals with the types Ghidra used.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.data.*;
import java.io.*;

public class ExportData extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work/re";
        PrintWriter w = new PrintWriter(new FileWriter(outDir + "/data.tsv"));
        w.println("addr\tname\tlen\ttype\tblock");
        Listing listing = currentProgram.getListing();
        SymbolTable st = currentProgram.getSymbolTable();
        for (Symbol s : st.getAllSymbols(true)) {
            if (s.getSymbolType() != SymbolType.LABEL) continue;
            MemoryBlock b = currentProgram.getMemory().getBlock(s.getAddress());
            if (b == null || b.isExecute()) continue;
            Data d = listing.getDataAt(s.getAddress());
            String type = d == null ? "?" : d.getDataType().getPathName();
            int len = d == null ? 0 : d.getLength();
            w.printf("%s\t%s\t%d\t%s\t%s\n", s.getAddress(), s.getName(), len, type, b.getName());
        }
        w.close();
        // Structure/typedef definitions referenced above, as C.
        PrintWriter t = new PrintWriter(new FileWriter(outDir + "/types.txt"));
        for (java.util.Iterator<DataType> it = currentProgram.getDataTypeManager().getAllDataTypes(); it.hasNext();) {
            DataType dt = it.next();
            if (dt instanceof Structure || dt instanceof Union || dt instanceof TypeDef || dt instanceof ghidra.program.model.data.Enum)
                t.printf("%s\t%d\t%s\n", dt.getPathName(), dt.getLength(), dt.getClass().getSimpleName());
        }
        t.close();
        println("data export done");
    }
}
