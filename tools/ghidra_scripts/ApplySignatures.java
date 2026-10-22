// Applies machine-code facts from re/callsites.tsv (tools/callsites.py):
// value-returning functions get a sized return type instead of void, and
// functions get at least as many stack parameters as their callers pass.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ApplySignatures extends GhidraScript {
    @Override
    public void run() throws Exception {
        String path = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work/re/callsites.tsv";
        BufferedReader r = new BufferedReader(new FileReader(path));
        String line = r.readLine();
        FunctionManager fm = currentProgram.getFunctionManager();
        int nret = 0, nparams = 0, nvar = 0;
        while ((line = r.readLine()) != null) {
            String[] f = line.split("\t");
            Function fn = fm.getFunctionAt(toAddr(Long.parseLong(f[0], 16)));
            if (fn == null) continue;
            int returns = Integer.parseInt(f[1]), size = Integer.parseInt(f[2]), arity = Integer.parseInt(f[3]);
            boolean variadic = f.length > 4 && f[4].equals("1");
            DataType cur = fn.getReturnType();
            if (returns != 0 && (cur instanceof VoidDataType || cur == DataType.DEFAULT || cur instanceof Undefined)) {
                DataType t = size == 1 ? Undefined1DataType.dataType : size == 2 ? Undefined2DataType.dataType : Undefined4DataType.dataType;
                fn.setReturnType(t, SourceType.ANALYSIS);
                fn.setSignatureSource(SourceType.ANALYSIS);  // decompiler honours only non-default signatures
                nret++;
            }
            int have = 0;
            for (Parameter p : fn.getParameters()) if (!p.isAutoParameter()) have++;
            if (variadic) {
                // Keep only the fixed parameters; the decompiler then takes the
                // argument count of each call from the stack cleanup.
                List<Variable> ps = new ArrayList<>();
                int k = 0;
                for (Parameter p : fn.getParameters()) {
                    if (p.isAutoParameter()) continue;
                    if (k++ < arity) ps.add(p);
                }
                for (int i = ps.size(); i < arity; i++)
                    ps.add(new ParameterImpl("param_" + (i + 1), Undefined4DataType.dataType, currentProgram));
                fn.replaceParameters(ps, Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, true, SourceType.ANALYSIS);
                fn.setVarArgs(true);
                fn.setSignatureSource(SourceType.ANALYSIS);
                nvar++;
                continue;
            }
            if (arity > have && arity < 32) {
                List<Variable> ps = new ArrayList<>();
                for (Parameter p : fn.getParameters()) if (!p.isAutoParameter()) ps.add(p);
                for (int i = have; i < arity; i++)
                    ps.add(new ParameterImpl("param_" + (i + 1), Undefined4DataType.dataType, currentProgram));
                fn.replaceParameters(ps, Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, true, SourceType.ANALYSIS);
                fn.setSignatureSource(SourceType.ANALYSIS);
                nparams++;
            }
        }
        r.close();
        println("return types set: " + nret + ", parameter lists extended: " + nparams + ", variadic: " + nvar);
    }
}
