/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (IA32用)                               */
/*    低レベル例外処理定義                                                  */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hosexp_h__
#define __HOS_V4__IA32__hosexp_h__
#include "linkage.h"
#include "pic.h"
#ifdef ASM

/* 割込み/例外共通開始処理  */
#define common_prologue(_sta_func,_exe_func)                      ;\
        /*  例外多重度インクリメント  */                          ;\
      	incl SYMBOL_NAME(_kernel_ia32__intrcnt)                   ;\
        /*  最初の例外?  */                                       ;\
	cmpl $1,SYMBOL_NAME(_kernel_ia32__intrcnt)                ;\
        /*  多重例外の場合, 直接ハンドラを呼び出す  */            ;\
	jne 1f                                                    ;\
        /*  最初の例外の場合は、スタック位置を保存してから  */    ;\
        /*  例外スタックへ切り替える                        */    ;\
	movl %esp,SYMBOL_NAME(_kernel_ia32__ktsksp)               ;\
	movl (SYMBOL_NAME(kernel_int_sp)),%esp	;                 ;\
        /*  例外処理開始宣言  */                                  ;\
	call SYMBOL_NAME(_sta_func)                               ;\
1:      /*  例外番号積み込み  */                                  ;\
        pushl %ebx                                                ;\
        /*  例外ハンドラ実行  */                                  ;\
	call  SYMBOL_NAME(_exe_func)                              ;\
        /*  例外復帰処理前に割り込み禁止にする  */                ;\
	cli                                                       ;

/* 割込み/例外共通完了処理  */
#define common_epilogue(_end_func)                                ;\
        /*  例外番号を取り除く  */                                ;\
	addl $4,%esp                                              ;\
        /*  例外多重度デクリメント  */                            ;\
	decl  SYMBOL_NAME(_kernel_ia32__intrcnt)                  ;\
        /*  多重例外処理中ならすぐに例外から復帰する  */          ;\
	jnz 2f                                                    ;\
        /*  最初の例外発生時のスタックに切り替える  */            ;\
	movl SYMBOL_NAME(_kernel_ia32__ktsksp),%esp               ;\
        /*  タスク独立部からタスク処理部に移るための処理を行う */ ;\
	call SYMBOL_NAME(_end_func)                               ;\
        /*   例外復帰処理へ  */                                   ;\
2:      jmp _kernel_ia32__ext_exc                                 ;



#define restore_context                  \
	popl    %ebx                    ;\
	popl    %ecx                    ;\
	popl    %edx                    ;\
	popl    %esi                    ;\
	popl    %edi                    ;\
	popl    %ebp                    ;\
	popl    %eax                    ;\
         /*  エラーコードを取り去る  */ ;\
	addl    $4,%esp		        ;\
	iret                            ;

#define	intr(excno)	                         \
	cld			                ;\
        /*  仮のエラーコードを積む  */          ;\
	pushl   $0		                ;\
	pushl   %eax                            ;\
	pushl   %ebp                            ;\
	pushl   %edi                            ;\
	pushl   %esi                            ;\
	pushl   %edx                            ;\
	pushl   %ecx                            ;\
	pushl   %ebx                            ;\
	movl	$(excno+PIC1_VBASE_ADDR),%ebx   ;\
	jmp     _kernel_ia32__common_intr	;



#define	exception(excno)	                 \
	cld			                ;\
        /*  仮のエラーコードを積む  */          ;\
	pushl   $0		                ;\
	pushl   %eax                            ;\
	pushl   %ebp                            ;\
	pushl   %edi                            ;\
	pushl   %esi                            ;\
	pushl   %edx                            ;\
	pushl   %ecx                            ;\
	pushl   %ebx                            ;\
	movl	$excno,%ebx  	                ;\
	jmp	_kernel_ia32__common_exc	;


#define	errexception(excno)	                 \
	cld			                ;\
	pushl   %eax                            ;\
	pushl   %ebp                            ;\
	pushl   %edi                            ;\
	pushl   %esi                            ;\
	pushl   %edx                            ;\
	pushl   %ecx                            ;\
	pushl   %ebx                            ;\
	movl	$excno,%ebx  	                ;\
	jmp	_kernel_ia32__common_exc	;

#else  /*  C言語のコード用  */
/*  例外総数  */
#define EXC_NR 20
/*  CPU例外番号  */
#define EXC_DIV       0
#define EXC_DEBUG     1
#define EXC_NMI       2
#define EXC_INT3      3
#define EXC_OVERFLOW  4
#define EXC_BOUND     5
#define EXC_OPCODE    6
#define EXC_DEVNAVL   7
#define EXC_DBLFLT    8
#define EXC_COSEGOR   9
#define EXC_INVTSS   10
#define EXC_SEGNPRS  11
#define EXC_STK      12
#define EXC_GENPROT  13
#define EXC_PFAULT   14
#define EXC_INTEL    15
#define EXC_COPRO    16
#define EXC_ALIGN    17
#define EXC_MACHCHK  18
#define EXC_SIMD     19
/*
 *  アセンブラレベルの例外低レベルルーチン群
 */
void _kernel_ia32__exc_divfault(void);
void _kernel_ia32__exc_debug(void);
void _kernel_ia32__exc_nmi(void);
void _kernel_ia32__exc_int3(void);
void _kernel_ia32__exc_overflow(void);
void _kernel_ia32__exc_bound(void);
void _kernel_ia32__exc_opcode(void);
void _kernel_ia32__exc_device_not_available(void);
void _kernel_ia32__exc_double_fault(void);
void _kernel_ia32__exc_coprocessor_segment_overrun(void);
void _kernel_ia32__exc_invalid_TSS(void);
void _kernel_ia32__exc_segment_not_present(void);
void _kernel_ia32__exc_stack_segment(void);
void _kernel_ia32__exc_general_protection(void);
void _kernel_ia32__exc_page_fault(void);
void _kernel_ia32__exc_intel_reserved(void);
void _kernel_ia32__exc_coprocessor_error(void);
void _kernel_ia32__exc_alignment_check(void);
void _kernel_ia32__exc_machine_check(void);
void _kernel_ia32__exc_simd_coprocessor(void);
/*
 *  アセンブラレベルの割り込み低レベルルーチン群
 */
void _kernel_ia32__intr0(void);
void _kernel_ia32__intr1(void);
void _kernel_ia32__intr2(void);
void _kernel_ia32__intr3(void);
void _kernel_ia32__intr4(void);
void _kernel_ia32__intr5(void);
void _kernel_ia32__intr6(void);
void _kernel_ia32__intr7(void);
void _kernel_ia32__intr8(void);
void _kernel_ia32__intr9(void);
void _kernel_ia32__intr10(void);
void _kernel_ia32__intr11(void);
void _kernel_ia32__intr12(void);
void _kernel_ia32__intr13(void);
void _kernel_ia32__intr14(void);
void _kernel_ia32__intr15(void);
void _kernel_ia32__user_trap_30(void);
void _kernel_ia32__user_trap_31(void);
void _kernel_ia32__user_trap_32(void);
void _kernel_ia32__user_trap_33(void);
void _kernel_ia32__user_trap_34(void);
void _kernel_ia32__user_trap_35(void);
void _kernel_ia32__user_trap_36(void);
void _kernel_ia32__user_trap_37(void);
void _kernel_ia32__user_trap_38(void);
void _kernel_ia32__user_trap_39(void);
void _kernel_ia32__user_trap_3a(void);
void _kernel_ia32__user_trap_3b(void);
void _kernel_ia32__user_trap_3c(void);
void _kernel_ia32__user_trap_3d(void);
void _kernel_ia32__user_trap_3e(void);
void _kernel_ia32__user_trap_3f(void);
void _kernel_ia32__user_trap_40(void);
void _kernel_ia32__user_trap_41(void);
void _kernel_ia32__user_trap_42(void);
void _kernel_ia32__user_trap_43(void);
void _kernel_ia32__user_trap_44(void);
void _kernel_ia32__user_trap_45(void);
void _kernel_ia32__user_trap_46(void);
void _kernel_ia32__user_trap_47(void);
void _kernel_ia32__user_trap_48(void);
void _kernel_ia32__user_trap_49(void);
void _kernel_ia32__user_trap_4a(void);
void _kernel_ia32__user_trap_4b(void);
void _kernel_ia32__user_trap_4c(void);
void _kernel_ia32__user_trap_4d(void);
void _kernel_ia32__user_trap_4e(void);
void _kernel_ia32__user_trap_4f(void);
void _kernel_ia32__user_trap_50(void);
void _kernel_ia32__user_trap_51(void);
void _kernel_ia32__user_trap_52(void);
void _kernel_ia32__user_trap_53(void);
void _kernel_ia32__user_trap_54(void);
void _kernel_ia32__user_trap_55(void);
void _kernel_ia32__user_trap_56(void);
void _kernel_ia32__user_trap_57(void);
void _kernel_ia32__user_trap_58(void);
void _kernel_ia32__user_trap_59(void);
void _kernel_ia32__user_trap_5a(void);
void _kernel_ia32__user_trap_5b(void);
void _kernel_ia32__user_trap_5c(void);
void _kernel_ia32__user_trap_5d(void);
void _kernel_ia32__user_trap_5e(void);
void _kernel_ia32__user_trap_5f(void);
void _kernel_ia32__user_trap_60(void);
void _kernel_ia32__user_trap_61(void);
void _kernel_ia32__user_trap_62(void);
void _kernel_ia32__user_trap_63(void);
void _kernel_ia32__user_trap_64(void);
void _kernel_ia32__user_trap_65(void);
void _kernel_ia32__user_trap_66(void);
void _kernel_ia32__user_trap_67(void);
void _kernel_ia32__user_trap_68(void);
void _kernel_ia32__user_trap_69(void);
void _kernel_ia32__user_trap_6a(void);
void _kernel_ia32__user_trap_6b(void);
void _kernel_ia32__user_trap_6c(void);
void _kernel_ia32__user_trap_6d(void);
void _kernel_ia32__user_trap_6e(void);
void _kernel_ia32__user_trap_6f(void);
void _kernel_ia32__user_trap_70(void);
void _kernel_ia32__user_trap_71(void);
void _kernel_ia32__user_trap_72(void);
void _kernel_ia32__user_trap_73(void);
void _kernel_ia32__user_trap_74(void);
void _kernel_ia32__user_trap_75(void);
void _kernel_ia32__user_trap_76(void);
void _kernel_ia32__user_trap_77(void);
void _kernel_ia32__user_trap_78(void);
void _kernel_ia32__user_trap_79(void);
void _kernel_ia32__user_trap_7a(void);
void _kernel_ia32__user_trap_7b(void);
void _kernel_ia32__user_trap_7c(void);
void _kernel_ia32__user_trap_7d(void);
void _kernel_ia32__user_trap_7e(void);
void _kernel_ia32__user_trap_7f(void);
void _kernel_ia32__user_trap_80(void);
void _kernel_ia32__user_trap_81(void);
void _kernel_ia32__user_trap_82(void);
void _kernel_ia32__user_trap_83(void);
void _kernel_ia32__user_trap_84(void);
void _kernel_ia32__user_trap_85(void);
void _kernel_ia32__user_trap_86(void);
void _kernel_ia32__user_trap_87(void);
void _kernel_ia32__user_trap_88(void);
void _kernel_ia32__user_trap_89(void);
void _kernel_ia32__user_trap_8a(void);
void _kernel_ia32__user_trap_8b(void);
void _kernel_ia32__user_trap_8c(void);
void _kernel_ia32__user_trap_8d(void);
void _kernel_ia32__user_trap_8e(void);
void _kernel_ia32__user_trap_8f(void);
void _kernel_ia32__user_trap_90(void);
void _kernel_ia32__user_trap_91(void);
void _kernel_ia32__user_trap_92(void);
void _kernel_ia32__user_trap_93(void);
void _kernel_ia32__user_trap_94(void);
void _kernel_ia32__user_trap_95(void);
void _kernel_ia32__user_trap_96(void);
void _kernel_ia32__user_trap_97(void);
void _kernel_ia32__user_trap_98(void);
void _kernel_ia32__user_trap_99(void);
void _kernel_ia32__user_trap_9a(void);
void _kernel_ia32__user_trap_9b(void);
void _kernel_ia32__user_trap_9c(void);
void _kernel_ia32__user_trap_9d(void);
void _kernel_ia32__user_trap_9e(void);
void _kernel_ia32__user_trap_9f(void);
void _kernel_ia32__user_trap_a0(void);
void _kernel_ia32__user_trap_a1(void);
void _kernel_ia32__user_trap_a2(void);
void _kernel_ia32__user_trap_a3(void);
void _kernel_ia32__user_trap_a4(void);
void _kernel_ia32__user_trap_a5(void);
void _kernel_ia32__user_trap_a6(void);
void _kernel_ia32__user_trap_a7(void);
void _kernel_ia32__user_trap_a8(void);
void _kernel_ia32__user_trap_a9(void);
void _kernel_ia32__user_trap_aa(void);
void _kernel_ia32__user_trap_ab(void);
void _kernel_ia32__user_trap_ac(void);
void _kernel_ia32__user_trap_ad(void);
void _kernel_ia32__user_trap_ae(void);
void _kernel_ia32__user_trap_af(void);
void _kernel_ia32__user_trap_b0(void);
void _kernel_ia32__user_trap_b1(void);
void _kernel_ia32__user_trap_b2(void);
void _kernel_ia32__user_trap_b3(void);
void _kernel_ia32__user_trap_b4(void);
void _kernel_ia32__user_trap_b5(void);
void _kernel_ia32__user_trap_b6(void);
void _kernel_ia32__user_trap_b7(void);
void _kernel_ia32__user_trap_b8(void);
void _kernel_ia32__user_trap_b9(void);
void _kernel_ia32__user_trap_ba(void);
void _kernel_ia32__user_trap_bb(void);
void _kernel_ia32__user_trap_bc(void);
void _kernel_ia32__user_trap_bd(void);
void _kernel_ia32__user_trap_be(void);
void _kernel_ia32__user_trap_bf(void);
void _kernel_ia32__user_trap_c0(void);
void _kernel_ia32__user_trap_c1(void);
void _kernel_ia32__user_trap_c2(void);
void _kernel_ia32__user_trap_c3(void);
void _kernel_ia32__user_trap_c4(void);
void _kernel_ia32__user_trap_c5(void);
void _kernel_ia32__user_trap_c6(void);
void _kernel_ia32__user_trap_c7(void);
void _kernel_ia32__user_trap_c8(void);
void _kernel_ia32__user_trap_c9(void);
void _kernel_ia32__user_trap_ca(void);
void _kernel_ia32__user_trap_cb(void);
void _kernel_ia32__user_trap_cc(void);
void _kernel_ia32__user_trap_cd(void);
void _kernel_ia32__user_trap_ce(void);
void _kernel_ia32__user_trap_cf(void);
void _kernel_ia32__user_trap_d0(void);
void _kernel_ia32__user_trap_d1(void);
void _kernel_ia32__user_trap_d2(void);
void _kernel_ia32__user_trap_d3(void);
void _kernel_ia32__user_trap_d4(void);
void _kernel_ia32__user_trap_d5(void);
void _kernel_ia32__user_trap_d6(void);
void _kernel_ia32__user_trap_d7(void);
void _kernel_ia32__user_trap_d8(void);
void _kernel_ia32__user_trap_d9(void);
void _kernel_ia32__user_trap_da(void);
void _kernel_ia32__user_trap_db(void);
void _kernel_ia32__user_trap_dc(void);
void _kernel_ia32__user_trap_dd(void);
void _kernel_ia32__user_trap_de(void);
void _kernel_ia32__user_trap_df(void);
void _kernel_ia32__user_trap_e0(void);
void _kernel_ia32__user_trap_e1(void);
void _kernel_ia32__user_trap_e2(void);
void _kernel_ia32__user_trap_e3(void);
void _kernel_ia32__user_trap_e4(void);
void _kernel_ia32__user_trap_e5(void);
void _kernel_ia32__user_trap_e6(void);
void _kernel_ia32__user_trap_e7(void);
void _kernel_ia32__user_trap_e8(void);
void _kernel_ia32__user_trap_e9(void);
void _kernel_ia32__user_trap_ea(void);
void _kernel_ia32__user_trap_eb(void);
void _kernel_ia32__user_trap_ec(void);
void _kernel_ia32__user_trap_ed(void);
void _kernel_ia32__user_trap_ee(void);
void _kernel_ia32__user_trap_ef(void);
void _kernel_ia32__user_trap_f0(void);
void _kernel_ia32__user_trap_f1(void);
void _kernel_ia32__user_trap_f2(void);
void _kernel_ia32__user_trap_f3(void);
void _kernel_ia32__user_trap_f4(void);
void _kernel_ia32__user_trap_f5(void);
void _kernel_ia32__user_trap_f6(void);
void _kernel_ia32__user_trap_f7(void);
void _kernel_ia32__user_trap_f8(void);
void _kernel_ia32__user_trap_f9(void);
void _kernel_ia32__user_trap_fa(void);
void _kernel_ia32__user_trap_fb(void);
void _kernel_ia32__user_trap_fc(void);
void _kernel_ia32__user_trap_fd(void);
void _kernel_ia32__user_trap_fe(void);
void _kernel_ia32__user_trap_ff(void);
#endif  /*  !ASM  */

#endif /*  __HOS_V4__IA32__hosexp_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
