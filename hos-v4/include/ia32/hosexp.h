/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*    プロセッサ抽象化コンポーネント (IA32用)                                    */
/*    低レベル例外処理定義                                                     */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hosexp_h__
#define __HOS_V4__IA32__hosexp_h__
#include "linkage.h"
#ifdef ASM

#define restore_context                  \
	popl    %ebx                    ;\
	popl    %ecx                    ;\
	popl    %edx                    ;\
	popl    %esi                    ;\
	popl    %edi                    ;\
	popl    %ebp                    ;\
	popl    %eax                    ;\
	addl    $4,%esp		        ;   /*  エラーコードを取り去る  */ \
	iret                            ;

#define	intr(excno)	         \
	cld			;\
	pushl   $0		;  /*  仮のエラーコード  */ \
	pushl   %eax            ;\
	pushl   %ebp            ;\
	pushl   %edi            ;\
	pushl   %esi            ;\
	pushl   %edx            ;\
	pushl   %ecx            ;\
	pushl   %ebx            ;\
        movl	$excno,%ebx	;\
	jmp     common_intr	;


/*  仮のエラーコードをプッシュする  */
#define	exception(excno)	 \
	cld			;\
	pushl   $0		;  /* 仮のエラーコード */ \
	pushl   %eax            ;\
	pushl   %ebp            ;\
	pushl   %edi            ;\
	pushl   %esi            ;\
	pushl   %edx            ;\
	pushl   %ecx            ;\
	pushl   %ebx            ;\
	movl	$excno,%ebx	;\
	jmp	common_intr	;


#define	errexception(excno)	 \
	cld			;\
	pushl   %eax            ;\
	pushl   %ebp            ;\
	pushl   %edi            ;\
	pushl   %esi            ;\
	pushl   %edx            ;\
	pushl   %ecx            ;\
	pushl   %ebx            ;\
	movl 	$excno,%ebx	;\
	jmp	common_intr	;


#else  /*  C言語のコード用  */
/*  例外総数  */
#define EXC_NR 20
/*  例外番号  */
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
void exp_divfault(void);
void exp_debug(void);
void exp_nmi(void);
void exp_int3(void);
void exp_overflow(void);
void exp_bound(void);
void exp_opcode(void);
void exp_device_not_available(void);
void exp_double_fault(void);
void exp_coprocessor_segment_overrun(void);
void exp_invalid_TSS(void);
void exp_segment_not_present(void);
void exp_stack_segment(void);
void exp_general_protection(void);
void exp_page_fault(void);
void exp_intel_reserved(void);
void exp_coprocessor_error(void);
void exp_alignment_check(void);
void exp_machine_check(void);
void exp_simd_coprocessor(void);
/*
 *  アセンブラレベルの割り込み低レベルルーチン群
 */
void intr0(void);
void intr1(void);
void intr2(void);
void intr3(void);
void intr4(void);
void intr5(void);
void intr6(void);
void intr7(void);
void intr8(void);
void intr9(void);
void intr10(void);
void intr11(void);
void intr12(void);
void intr13(void);
void intr14(void);
void intr15(void);
void unknown_intr(void);
#endif  /*  !ASM  */

#endif /*  __HOS_V4__IA32__hosexp_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
