// Undo RetypePointers: variables and globals typed `u8 *` go back to undefined4.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.util.*;

public class RevertPointers extends GhidraScript {
    static boolean isBytePtr(DataType dt) {
        return dt instanceof Pointer && ((Pointer) dt).getDataType() != null
            && ((Pointer) dt).getDataType().getName().equals("u8");
    }

    @Override
    public void run() throws Exception {
        int n = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            for (Variable v : f.getAllVariables()) {
                if (isBytePtr(v.getDataType())) {
                    v.setDataType(Undefined4DataType.dataType, SourceType.ANALYSIS);
                    n++;
                }
            }
            if (isBytePtr(f.getReturnType())) f.setReturnType(Undefined4DataType.dataType, SourceType.ANALYSIS);
        }
        int g = 0;
        DataIterator it = currentProgram.getListing().getDefinedData(true);
        List<Data> back = new ArrayList<>();
        while (it.hasNext()) { Data d = it.next(); if (isBytePtr(d.getDataType())) back.add(d); }
        for (Data d : back) {
            currentProgram.getListing().clearCodeUnits(d.getAddress(), d.getMaxAddress(), false);
            currentProgram.getListing().createData(d.getAddress(), Undefined4DataType.dataType);
            g++;
        }
        println("reverted " + n + " variables, " + g + " globals");
    }
}
