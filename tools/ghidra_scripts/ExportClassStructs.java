// Dumps the fields of every recovered class struct (C_xxxxxxxx) and the
// methods in each class namespace: re/class_fields.tsv  class offset size name.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import java.io.*;
import java.util.*;

public class ExportClassStructs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String root = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work";
        PrintWriter w = new PrintWriter(new FileWriter(root + "/re/class_fields.tsv"));
        w.println("class\toffset\tsize\tname");
        Iterator<DataType> it = currentProgram.getDataTypeManager().getAllDataTypes();
        int n = 0;
        while (it.hasNext()) {
            DataType dt = it.next();
            if (!(dt instanceof Structure) || !dt.getName().matches("C_[0-9a-f]{8}(_[0-9a-f]+)?")) continue;
            for (DataTypeComponent c : ((Structure) dt).getDefinedComponents()) {
                if (c.getFieldName() == null || !c.getFieldName().startsWith("field_")) continue;
                w.printf("%s\t%d\t%d\t%s\n", dt.getName(), c.getOffset(), c.getLength(), c.getFieldName());
                n++;
            }
        }
        w.close();
        PrintWriter m = new PrintWriter(new FileWriter(root + "/re/class_methods.tsv"));
        m.println("class\tmethod");
        for (ghidra.program.model.listing.Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String ns = f.getParentNamespace().getName();
            if (ns.matches("C_[0-9a-f]{8}(_[0-9a-f]+)?")) m.printf("%s\t%s\n", ns, f.getEntryPoint());
        }
        m.close();
        println("exported " + n + " class fields");
    }
}
