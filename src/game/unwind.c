/*
 * Functions whose cleanup runs through MSVC unwind funclets (small `call $L`
 * blocks executing with the parent's EBP) that the generator could not
 * translate.  The funclets are inlined here as plain destructor calls on the
 * parent's own locals; exception-frame bookkeeping (fs:[0], trylevel) is
 * dropped.
 */
#include "game.h"

/* Value an MSVC function returns in EAX after its epilogue restored fs:[0]:
   the previous SEH list head, i.e. the current fs:[0] (we push no frame). */
static inline undefined4 seh_list_head(void)
{
    undefined4 r;
#if defined(__i386__) && !defined(CIV2_NATIVE)
    __asm__ volatile ("movl %%fs:0, %0" : "=r"(r));
#else
    r = 0;      /* no SEH chain outside 32-bit Windows */
#endif
    return r;
}

/* 0x0044ca60: destructor - destroys the member at this+0x10, then the base. */
undefined4 __thiscall FUN_0044ca60(void *this)
{
    void *member;

    /* funclet 0044caab */
    member = (this != NULL) ? (void *)((iptr)this + 0x10) : NULL;
    thunk_FUN_0044ca40(member);
    /* funclet 0044cad3 */
    FUN_005db650(this);
    return seh_list_head();
}

/* 0x0044cba0: destructor - resets the vtable, clears this+0x110, destroys
   the member at this+0x48, then the base. */
void __thiscall FUN_0044cba0(void *this)
{
    void *member;

    *(undefined ***)this = &PTR_FUN_0061c060;
    *(undefined4 *)((iptr)this + 0x110) = 0;
    /* funclet 0044cc01 */
    member = (this != NULL) ? (void *)((iptr)this + 0x48) : NULL;
    thunk_FUN_0044cb20(member);
    /* funclet 0044cc29 */
    FUN_005bd915(this);
}

/* 0x004f3e70: destructor - destroys the member at this+0x4a4, then the base. */
void __thiscall FUN_004f3e70(void *this)
{
    void *member;

    /* funclet 004f3ebb */
    member = (this != NULL) ? (void *)((iptr)this + 0x4a4) : NULL;
    thunk_FUN_0059df8a(member);
    /* funclet 004f3ee5 */
    thunk_FUN_0043c110(this);
}

/* 0x005efeb0: destructor - releases the handle at this+0xb0, runs the
   cleanup, destroys the members at this+0xc0 and this+0x44, then the base. */
void __thiscall FUN_005efeb0(void *this)
{
    void *member;

    *(undefined4 *)((iptr)this + 0xb0) = FUN_005ef5db(*(undefined4 *)((iptr)this + 0xb0));
    FUN_005f029e(this);
    /* funclet 005eff2b */
    FUN_005f04c0((void *)((iptr)this + 0xc0));
    /* funclet 005eff3a */
    member = (this != NULL) ? (void *)((iptr)this + 0x44) : NULL;
    thunk_FUN_0044ca40(member);
    /* funclet 005eff62 */
    FUN_005e5ee0(this);
}

/* 0x0055c3d3: "PICKGOVT" dialog - lets civ param_1 pick a government
   (param_2 != 0: all of them, including anarchy) and applies the choice. */
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define local_30c (*(int *)(frame_ + FRAME_OFF(0)))
#define local_308 (*(undefined1 (*)[756])(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(760)))
void __cdecl FUN_0055c3d3(int param_1, int param_2)
{
    undefined4 uVar2;
    undefined1 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */

    thunk_FUN_0059db08(local_308, 0x4000);
    if ((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) == 0) {
        /* nothing */
    }
    else if ((game.multiplayer < 3) || (DAT_006d1da0 == param_1)) {
        thunk_FUN_0043c9d0(local_308, s_PICKGOVT_00633acc);
        for (local_14 = (param_2 != 0) ? 0 : 1; local_14 < 7; local_14 = local_14 + 1) {
            /* (FUN_0055c277's last 19 parameters are a decompiler artifact) */
            if ((param_2 != 0) || (thunk_FUN_0055c277(param_1, local_14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) != 0)) {
                thunk_FUN_0040bbb0();
                thunk_FUN_0040ff00(government_names[local_14]);
                thunk_FUN_0059edf0(local_308, &DAT_00679640, local_14, 0);
            }
        }
        local_30c = thunk_FUN_0040bc80(local_308, 0);
        if (-1 < local_30c) {
            thunk_FUN_0055c066(param_1, local_30c);
            thunk_FUN_0046e020(0x14, 1, 0, 0);
            uVar2 = (undefined4)thunk_FUN_00493b10(param_1);
            thunk_FUN_0040ff60(0, uVar2);
            uVar2 = (undefined4)thunk_FUN_00493ba6(param_1);
            thunk_FUN_0040ff60(1, uVar2);
            uVar2 = thunk_FUN_00410070(param_1);
            thunk_FUN_0040ff60(2, uVar2);
            thunk_FUN_004271e8(3, government_names[local_30c]);
            thunk_FUN_00410030(s_NEWGOVT_00633ad8, &DAT_00646878 + local_30c * 0x3c, 0);
            if (((4 < local_30c) && (((*(undefined1 *)((char *)&game.game_options + 1)) & 1) != 0)) &&
                ((game.field_0c & 0x20) == 0)) {
                thunk_FUN_004271e8(0, government_names[local_30c]);
                thunk_FUN_004904c0(PTR_s_TUTORIAL_00627678, s_DEMOCRATS_00633ae0, &DAT_00643af8, 0);
                game.field_0c = game.field_0c | 0x20;
            }
        }
    }
    else {
        thunk_FUN_0046b14d(0x9f, *(undefined4 *)
                                 (&DAT_006ad30c + *(int *)(&DAT_006ad558 + param_1 * 4) * 0x54),
                           param_2, 0, 0, 0, 0, 0, 0, 0);
    }
    /* funclet 0055c679 */
    thunk_FUN_0059df8a(local_308);
}
#undef DAT_006d1da0
#undef local_30c
#undef local_308
#undef local_14

/* 0x00493e83: builds a temporary object, stores param_1 in it, runs it if
   its check succeeds, then destroys it. */
#define local_1f8 (*(undefined1 (*)[476])(frame_ + FRAME_OFF(0)))
#define local_1c (*(undefined4 *)(frame_ + FRAME_OFF(476)))
void __cdecl FUN_00493e83(undefined4 param_1)
{
    int iVar1;
    undefined1 frame_[FRAME_OFF(504)] __attribute__((aligned(8)));  /* original stack frame */

    thunk_FUN_0049621d(local_1f8);
    local_1c = param_1;
    iVar1 = thunk_FUN_00496402(local_1f8);
    if (iVar1 != 0) {
        thunk_FUN_004965ff(local_1f8);
    }
    /* funclet 00493eeb: lea ecx,[ebp-0x1f4] */
    thunk_FUN_0049632a(local_1f8);
}
#undef local_1f8
#undef local_1c

/* 0x005e0863: builds a window with "OK"/"Cancel" buttons on the stack and
   tears it all down again; returns 0. */
#define local_630 (*(undefined1 (*)[60])(frame_ + FRAME_OFF(0)))
#define local_5f4 (*(undefined1 (*)[8])(frame_ + FRAME_OFF(60)))
#define local_5ec (*(undefined1 (*)[1076])(frame_ + FRAME_OFF(68)))
#define local_1b8 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(1144)))
#define local_170 (*(undefined1 (*)[204])(frame_ + FRAME_OFF(1216)))
#define local_a4 (*(undefined1 (*)[60])(frame_ + FRAME_OFF(1420)))
#define local_68 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(1480)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(1552)))
undefined4 __cdecl FUN_005e0863(void)
{
    int iVar1;
    int iVar2;
    undefined1 frame_[FRAME_OFF(1584)] __attribute__((aligned(8)));  /* original stack frame */

    FUN_005c64da(local_5ec);
    thunk_FUN_0044c5a0(local_1b8);
    thunk_FUN_0043c690(local_5f4);
    thunk_FUN_0040f3e0(local_630);
    thunk_FUN_0040f3e0(local_a4);
    thunk_FUN_004187a0(local_68);
    thunk_FUN_00417ef0(local_5f4, 0, 0x11);
    FUN_005d8236(local_5f4);
    FUN_005d268e(local_5f4);
    SetRect(&local_20, 0, 0, 0x3c, 0x19);
    iVar1 = thunk_FUN_004710a0(local_1b8);
    iVar1 = iVar1 + -0x23;
    iVar2 = thunk_FUN_00471070(local_1b8);
    OffsetRect(&local_20, iVar2 + -0x46, iVar1);
    thunk_FUN_0040f680(local_630, (undefined4)local_170, 0x65, (undefined4)&local_20,
                       (undefined4)&DAT_00638d90);
    thunk_FUN_0040f880(local_630, (undefined4)FUN_005e00bb);
    OffsetRect(&local_20, 0, -0x23);
    thunk_FUN_0040f680(local_a4, (undefined4)local_170, 0x66, (undefined4)&local_20,
                       (undefined4)s_Cancel_00638d94);
    thunk_FUN_0040f880(local_a4, (undefined4)FUN_005e00bb);
    /* funclets 005e0a31..005e0a6a: destroy the locals in reverse order */
    thunk_FUN_00418870(local_68);
    thunk_FUN_0040f570(local_a4);
    thunk_FUN_0040f570(local_630);
    thunk_FUN_0043c520(local_5f4);
    thunk_FUN_0044cba0(local_1b8);
    FUN_005c656b(local_5ec);
    return 0;
}
#undef local_630
#undef local_5f4
#undef local_5ec
#undef local_1b8
#undef local_170
#undef local_a4
#undef local_68
#undef local_20

/* 0x004d53ab: loads picture 0x1f1 and cuts it into six button images
   (two rows of three; the second row's caption depends on the language). */
#define local_68 (*(undefined1 (*)[72])(frame_ + FRAME_OFF(0)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(72)))
void __thiscall FUN_004d53ab(void *this)
{
    int iVar1;
    undefined4 uVar2;
    undefined1 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */

    FUN_005bd630(local_68);
    FUN_005c19ad(0x8b);
    iVar1 = FUN_005bf5e1(local_68, 0x1f1, 10, 0xec, (void *)((iptr)this + 0x1f8));
    if (iVar1 != 0) {
        thunk_FUN_0040bbb0();
        uVar2 = (undefined4)thunk_FUN_00428b0c(*(undefined4 *)(DAT_00628420 + 0x3f8));
        thunk_FUN_0040bbe0(uVar2);
        SetRect(&local_20, 0, 0, 0x34, 0x24);
        OffsetRect(&local_20, 1, 1);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0x978), (undefined4)local_68, 9, 1, 1, 0x34, 0x24);
        OffsetRect(&local_20, 0x35, 0);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0x9f0), (undefined4)local_68, 9, 0x36, 1, 0x34, 0x24);
        OffsetRect(&local_20, 0x35, 0);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0x9b4), (undefined4)local_68, 9, 0x6b, 1, 0x34, 0x24);
        FUN_005c19ad(0xc6);
        thunk_FUN_0040bbb0();
        if (DAT_00628064 == 0) {
            uVar2 = (undefined4)thunk_FUN_00428b0c(*(undefined4 *)(DAT_00628420 + 0x354));
            thunk_FUN_0040bbe0(uVar2);
        }
        else if (DAT_00628064 == 1) {
            thunk_FUN_0040bbe0(s_Lancer_0062e324);
        }
        else if (DAT_00628064 == 2) {
            thunk_FUN_0040bbe0(s_Starten_0062e32c);
        }
        SetRect(&local_20, 0, 0, 0x43, 0x24);
        OffsetRect(&local_20, 1, 0x26);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0xa2c), (undefined4)local_68, 9, 1, 0x26, 0x43, 0x24);
        OffsetRect(&local_20, 0x44, 0);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0xaa4), (undefined4)local_68, 9, 0x45, 0x26, 0x43, 0x24);
        OffsetRect(&local_20, 0x44, 0);
        FUN_005c1020(local_68, (undefined4 *)((iptr)this + 0x8d4), (undefined4)&DAT_00679640, (LONG *)&local_20, 0);
        FUN_005cedad((void *)((iptr)this + 0xa68), (undefined4)local_68, 9, 0x89, 0x26, 0x43, 0x24);
    }
    /* funclet 004d56ea: lea ecx,[ebp-0x64] */
    FUN_005bd915(local_68);
}
#undef local_68
#undef local_20
