// Types integer variables that hold addresses as pointer-sized integers
// (iptr / uptr: int / unsigned on the original 32-bit machine).
//
// The decompiler leaves a value that is used as an address typed `int`
// unless told otherwise, so the C reads `*(int *)(param_1 + 4)` -- correct on
// a 32-bit machine only.  For locals, parameters and globals of pointer size
// whose value flows (through additions, copies and joins) into the address
// of a memory load or store, commit `u8 *`: byte-pointer arithmetic means
// the same thing as the original integer arithmetic, and is portable.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.address.Address;
import java.util.*;

public class RetypePointers extends GhidraScript {
    DataType iptr, uptr;

    static boolean isUnsigned(DataType dt) {
        if (dt instanceof TypeDef) dt = ((TypeDef) dt).getBaseDataType();
        return dt instanceof AbstractIntegerDataType && !((AbstractIntegerDataType) dt).isSigned();
    }

    DataType ptrInt(DataType current) {
        return isUnsigned(current) ? uptr : iptr;     // keep the original signedness
    }

    static boolean isIntish(DataType dt) {
        if (dt instanceof TypeDef) dt = ((TypeDef) dt).getBaseDataType();
        return dt.getLength() == 4 && (dt instanceof Undefined || dt instanceof AbstractIntegerDataType || dt == DataType.DEFAULT);
    }

    /** Does a value defined by vn reach a LOAD/STORE address within a few steps? */
    static boolean usedAsAddress(Varnode vn, int depth, Set<Varnode> seen) {
        if (depth > 4 || !seen.add(vn)) return false;
        Iterator<PcodeOp> it = vn.getDescendants();
        while (it.hasNext()) {
            PcodeOp op = it.next();
            int oc = op.getOpcode();
            if ((oc == PcodeOp.LOAD || oc == PcodeOp.STORE) && op.getInput(1) == vn) return true;
            if (oc == PcodeOp.INT_ADD || oc == PcodeOp.INT_SUB || oc == PcodeOp.PTRADD || oc == PcodeOp.PTRSUB
                || oc == PcodeOp.COPY || oc == PcodeOp.MULTIEQUAL || oc == PcodeOp.INDIRECT || oc == PcodeOp.CAST) {
                // INT_ADD/INT_SUB: only if this value is the base, not an index scaled by a multiply
                Varnode out = op.getOutput();
                if (out != null && out.getSize() == 4 && usedAsAddress(out, depth + 1, seen)) return true;
            }
        }
        return false;
    }

    static boolean pointerish(DataType dt) {
        if (dt == null) return false;
        if (dt instanceof Pointer) return true;
        String n = dt.getName();
        return n.equals("iptr") || n.equals("uptr");
    }

    /** Assigned from a pointer (cast or copy of a pointer-typed value)? */
    static boolean assignedFromPointer(HighVariable hv) {
        for (Varnode vn : hv.getInstances()) {
            PcodeOp def = vn.getDef();
            if (def == null) continue;
            int oc = def.getOpcode();
            if ((oc == PcodeOp.CAST || oc == PcodeOp.COPY) && def.getInput(0).getHigh() != null
                && pointerish(def.getInput(0).getHigh().getDataType())) return true;
        }
        return false;
    }

    static boolean anyInstanceUsedAsAddress(HighVariable hv) {
        for (Varnode vn : hv.getInstances())
            if (usedAsAddress(vn, 0, new HashSet<>())) return true;
        return false;
    }

    /** Used directly in an operation that only makes sense on integers? */
    static boolean usedAsInteger(HighVariable hv) {
        for (Varnode vn : hv.getInstances()) {
            Iterator<PcodeOp> it = vn.getDescendants();
            while (it.hasNext()) {
                int oc = it.next().getOpcode();
                if (oc == PcodeOp.INT_MULT || oc == PcodeOp.INT_DIV || oc == PcodeOp.INT_SDIV || oc == PcodeOp.INT_REM
                    || oc == PcodeOp.INT_SREM || oc == PcodeOp.INT_LEFT || oc == PcodeOp.INT_RIGHT || oc == PcodeOp.INT_SRIGHT
                    || oc == PcodeOp.INT_LESS || oc == PcodeOp.INT_SLESS || oc == PcodeOp.INT_LESSEQUAL
                    || oc == PcodeOp.INT_SLESSEQUAL || oc == PcodeOp.INT_AND || oc == PcodeOp.INT_OR
                    || oc == PcodeOp.INT_XOR || oc == PcodeOp.INT_2COMP || oc == PcodeOp.INT_NEGATE
                    || oc == PcodeOp.INT_SEXT || oc == PcodeOp.INT_ZEXT || oc == PcodeOp.SUBPIECE)
                    return true;
            }
        }
        return false;
    }

    @Override
    public void run() throws Exception {
        iptr = currentProgram.getDataTypeManager().getDataType("/iptr");
        uptr = currentProgram.getDataTypeManager().getDataType("/uptr");
        if (iptr == null || uptr == null) throw new Exception("run ApplyTypes first (iptr/uptr)");
        DecompInterface ifc = new DecompInterface();
        ifc.toggleCCode(false);
        ifc.toggleSyntaxTree(true);
        ifc.openProgram(currentProgram);
        int nvar = 0, nfun = 0;
        Map<Address, Integer> gvotes = new HashMap<>();
        Map<Function, Set<Integer>> paramVotes = new HashMap<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (monitor.isCancelled()) break;
            if (f.isThunk() || f.getEntryPoint().getOffset() >= 0x5f1b80L) continue;
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            if (r == null || !r.decompileCompleted()) continue;
            HighFunction hf = r.getHighFunction();
            boolean changed = false;
            List<HighSymbol> syms = new ArrayList<>();
            Iterator<HighSymbol> it = hf.getLocalSymbolMap().getSymbols();
            while (it.hasNext()) syms.add(it.next());
            for (HighSymbol hs : syms) {
                // Only parameters and named stack variables: the decompiler's
                // register temporaries (iVar1...) often merge unrelated values.
                if (hs.getName().equals("this") || !isIntish(hs.getDataType())) continue;
                HighVariable hv = hs.getHighVariable();
                if (hv == null || !(anyInstanceUsedAsAddress(hv) || assignedFromPointer(hv))) continue;
                try {
                    HighFunctionDBUtil.updateDBVariable(hs, null, ptrInt(hs.getDataType()), SourceType.ANALYSIS);
                    nvar++;
                    changed = true;
                } catch (Exception e) { }
            }
            Iterator<HighSymbol> git = hf.getGlobalSymbolMap().getSymbols();
            while (git.hasNext()) {
                HighSymbol hs = git.next();
                if (!hs.getStorage().isMemoryStorage() || !isIntish(hs.getDataType())) continue;
                HighVariable hv = hs.getHighVariable();
                if (hv != null && anyInstanceUsedAsAddress(hv))
                    gvotes.merge(hs.getStorage().getMinAddress(), isUnsigned(hs.getDataType()) ? 1 : 1000, Integer::sum);
            }
            // Parameters of callees that receive pointers here.
            Iterator<PcodeOpAST> ops = hf.getPcodeOps();
            while (ops.hasNext()) {
                PcodeOpAST op = ops.next();
                if (op.getOpcode() != PcodeOp.CALL) continue;
                Function callee = getFunctionAt(op.getInput(0).getAddress());
                if (callee == null) continue;
                if (callee.isThunk()) callee = callee.getThunkedFunction(true);
                for (int i = 1; i < op.getNumInputs(); i++) {
                    Varnode a = op.getInput(i);
                    if (a.getHigh() != null && pointerish(a.getHigh().getDataType()))
                        paramVotes.computeIfAbsent(callee, k -> new HashSet<>()).add(i - 1);
                }
            }
            if (changed) nfun++;
        }
        ifc.dispose();
        int np = 0;
        for (Map.Entry<Function, Set<Integer>> e : paramVotes.entrySet()) {
            Function callee = e.getKey();
            if (callee.getEntryPoint().getOffset() >= 0x5f1b80L) continue;
            Parameter[] ps = callee.getParameters();
            for (int i : e.getValue()) {
                if (i >= ps.length || ps[i].isAutoParameter() || !isIntish(ps[i].getDataType())) continue;
                try { ps[i].setDataType(ptrInt(ps[i].getDataType()), SourceType.ANALYSIS); np++; } catch (Exception ex) { }
            }
        }
        println("parameters receiving pointers: " + np);
        int ng = 0;
        Listing listing = currentProgram.getListing();
        for (Address a : gvotes.keySet()) {
            Data d = listing.getDataAt(a);
            if (d != null && d.getDataType() instanceof Structure) continue;
            try {
                DataUtilities.createData(currentProgram, a, gvotes.get(a) >= 1000 ? iptr : uptr, -1, false,
                    DataUtilities.ClearDataMode.CLEAR_ALL_UNDEFINED_CONFLICT_DATA);
                ng++;
            } catch (Exception e) { }
        }
        println("pointer-typed " + nvar + " variables in " + nfun + " functions, " + ng + " globals");
    }
}
