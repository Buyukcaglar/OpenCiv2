// Gives signless ("undefinedN") locals and parameters a signed or unsigned
// integer type according to the p-code operations that consume them.
//
// The decompiler prints no casts for undefined types, so `local_8 < 0` is
// ambiguous: the original may have compared signed (jl/jge) or unsigned
// (jb/jae).  Committing concrete types makes the printer emit the casts that
// pin down the original semantics.  Variables used both ways get the signed
// type; the printer then casts the unsigned uses.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.SourceType;
import java.util.*;

public class RetypeSignedness extends GhidraScript {
    static boolean isSigned(int op) {
        return op == PcodeOp.INT_SLESS || op == PcodeOp.INT_SLESSEQUAL || op == PcodeOp.INT_SRIGHT
            || op == PcodeOp.INT_SDIV || op == PcodeOp.INT_SREM || op == PcodeOp.INT_SEXT
            || op == PcodeOp.INT_SCARRY || op == PcodeOp.INT_SBORROW || op == PcodeOp.FLOAT_INT2FLOAT;
    }

    static boolean isUnsigned(int op) {
        return op == PcodeOp.INT_LESS || op == PcodeOp.INT_LESSEQUAL || op == PcodeOp.INT_RIGHT
            || op == PcodeOp.INT_DIV || op == PcodeOp.INT_REM || op == PcodeOp.INT_ZEXT
            || op == PcodeOp.INT_CARRY;
    }

    static DataType intType(int size, boolean signed) {
        switch (size) {
            case 1: return signed ? (DataType) SignedCharDataType.dataType : UnsignedCharDataType.dataType;
            case 2: return signed ? (DataType) ShortDataType.dataType : UnsignedShortDataType.dataType;
            case 4: return signed ? (DataType) IntegerDataType.dataType : UnsignedIntegerDataType.dataType;
            case 8: return signed ? (DataType) LongLongDataType.dataType : UnsignedLongLongDataType.dataType;
        }
        return null;
    }

    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.toggleCCode(false);
        ifc.toggleSyntaxTree(true);
        ifc.openProgram(currentProgram);
        long crtStart = 0x5f1b80L;
        int nfun = 0, nvar = 0;
        Map<ghidra.program.model.address.Address, int[]> gvotes = new HashMap<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (monitor.isCancelled()) break;
            if (f.isThunk() || f.getEntryPoint().getOffset() >= crtStart) continue;
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            if (r == null || !r.decompileCompleted()) continue;
            HighFunction hf = r.getHighFunction();
            boolean changed = false;
            Iterator<HighSymbol> it = hf.getLocalSymbolMap().getSymbols();
            List<HighSymbol> syms = new ArrayList<>();
            while (it.hasNext()) syms.add(it.next());
            for (HighSymbol hs : syms) {
                DataType dt = hs.getDataType();
                if (!(dt instanceof Undefined) && !(dt == DataType.DEFAULT)) continue;
                HighVariable hv = hs.getHighVariable();
                if (hv == null) continue;
                int signedUses = 0, unsignedUses = 0;
                for (Varnode vn : hv.getInstances()) {
                    Iterator<PcodeOp> uses = vn.getDescendants();
                    while (uses.hasNext()) {
                        int op = uses.next().getOpcode();
                        if (isSigned(op)) signedUses++;
                        else if (isUnsigned(op)) unsignedUses++;
                    }
                }
                if (signedUses == 0 && unsignedUses == 0) continue;
                DataType nt = intType(dt.getLength(), signedUses > 0);
                if (nt == null) continue;
                try {
                    HighFunctionDBUtil.updateDBVariable(hs, null, nt, SourceType.ANALYSIS);
                    nvar++;
                    changed = true;
                } catch (Exception e) {
                    // parameters of functions without committed signatures etc.
                }
            }
            Iterator<HighSymbol> git = hf.getGlobalSymbolMap().getSymbols();
            while (git.hasNext()) {
                HighSymbol hs = git.next();
                DataType dt = hs.getDataType();
                if (!(dt instanceof Undefined) || !hs.getStorage().isMemoryStorage()) continue;
                HighVariable hv = hs.getHighVariable();
                if (hv == null) continue;
                int[] v = gvotes.computeIfAbsent(hs.getStorage().getMinAddress(), k -> new int[3]);
                v[2] = dt.getLength();
                for (Varnode vn : hv.getInstances()) {
                    Iterator<PcodeOp> uses = vn.getDescendants();
                    while (uses.hasNext()) {
                        int op = uses.next().getOpcode();
                        if (isSigned(op)) v[0]++;
                        else if (isUnsigned(op)) v[1]++;
                    }
                }
            }
            if (changed) nfun++;
            if (nfun % 200 == 0 && changed) println("retyped variables in " + nfun + " functions so far");
        }
        ifc.dispose();
        int nglob = 0;
        Listing listing = currentProgram.getListing();
        for (Map.Entry<ghidra.program.model.address.Address, int[]> e : gvotes.entrySet()) {
            int[] v = e.getValue();
            if (v[0] == 0 && v[1] == 0) continue;
            DataType nt = intType(v[2], v[0] > 0);
            if (nt == null) continue;
            Data d = listing.getDataAt(e.getKey());
            if (d != null && !(d.getDataType() instanceof Undefined) && d.getDataType() != DataType.DEFAULT) continue;
            try {
                DataUtilities.createData(currentProgram, e.getKey(), nt, -1, false,
                    DataUtilities.ClearDataMode.CLEAR_ALL_UNDEFINED_CONFLICT_DATA);
                nglob++;
            } catch (Exception ex) { }
        }
        println("retyped " + nvar + " variables in " + nfun + " functions, " + nglob + " globals");
    }
}
