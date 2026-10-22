// Merges function fragments (re/fragments.tsv, from tools/fragments.py) back
// into their parent functions: deletes the fragment's function definition,
// turns the parent's "tail call" into the plain jump it really is, and
// recomputes the parent's body so it includes the tail.
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class MergeFragments extends GhidraScript {
    @Override
    public void run() throws Exception {
        String path = getScriptArgs().length > 0 ? getScriptArgs()[0] : "/work/re/fragments.tsv";
        BufferedReader r = new BufferedReader(new FileReader(path));
        String line = r.readLine();
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        List<Function> parents = new ArrayList<>();
        int n = 0, fixed = 0;
        while ((line = r.readLine()) != null) {
            String[] f = line.split("\t");
            Address fa = toAddr(Long.parseLong(f[0], 16));
            Function frag = fm.getFunctionAt(fa);
            Function parent = fm.getFunctionAt(toAddr(Long.parseLong(f[1], 16)));
            if (frag != null) { fm.removeFunction(fa); n++; }
            List<Reference> refs = new ArrayList<>();
            for (Reference ref : rm.getReferencesTo(fa)) refs.add(ref);
            for (Reference ref : refs) {
                Instruction ins = listing.getInstructionAt(ref.getFromAddress());
                if (ins == null || !ins.getMnemonicString().equals("JMP")) continue;
                ins.setFlowOverride(FlowOverride.NONE);
                rm.delete(ref);
                rm.addMemoryReference(ref.getFromAddress(), fa, RefType.UNCONDITIONAL_JUMP, SourceType.ANALYSIS, ref.getOperandIndex());
                fixed++;
            }
            if (parent != null) parents.add(parent);
        }
        r.close();
        for (Function p : parents)
            CreateFunctionCmd.fixupFunctionBody(currentProgram, p, monitor);
        println("merged " + n + " fragments, fixed " + fixed + " jumps");
    }
}
