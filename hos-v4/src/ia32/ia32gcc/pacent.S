/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*   プロセッサ抽象化コンポーネント (IA32用)  割込み関連処理                       */
/*                                            (割込みエントリ)                */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#define ASM 1
#include "hosexp.h"
.bss
ALIGN
WVAR(intrcnt)
WVAR(ktsksp)	
.text
.globl kernel_int_sp		; 
.globl intrcnt,ktsksp			; 
ENTRY(common_intr)
	incl SYMBOL_NAME(intrcnt)
	cmpl $1,SYMBOL_NAME(intrcnt)
	jne 1f
	movl %esp,SYMBOL_NAME(ktsksp)               /*  スタック切り替え  */
	movl (SYMBOL_NAME(kernel_int_sp)),%esp	;
	call SYMBOL_NAME(kernel_sta_int)
1:	pushl %ebx		;                   /*  割込み/例外番号  */
	call SYMBOL_NAME(kernel_exe_int) 
	call SYMBOL_NAME(send_eoi)    /*  割込み/例外番号がつまれているはず  */
	addl $4,%esp
	cli
	decl  SYMBOL_NAME(intrcnt)
	jnz 2f
	movl SYMBOL_NAME(ktsksp),%esp               /*  スタック切り替え  */
	call SYMBOL_NAME(kernel_end_int)
2:      jmp ext_exp
	
		
ENTRY(exp_divfault)
	exception(0)

ENTRY(exp_debug)
	exception(1)

ENTRY(exp_nmi)
	exception(2)

ENTRY(exp_int3)
	exception(3)

ENTRY(exp_overflow)
	exception(4)

ENTRY(exp_bound)
	exception(5)

ENTRY(exp_opcode)
	exception(6)

ENTRY(exp_device_not_available)
	exception(7)

ENTRY(exp_double_fault)
	exception(8)

ENTRY(exp_coprocessor_segment_overrun)
	exception(9)

ENTRY(exp_invalid_TSS)
	exception(10)

ENTRY(exp_segment_not_present)
	exception(11)

ENTRY(exp_stack_segment)
	exception(12)

ENTRY(exp_general_protection)
	exception(13)

ENTRY(exp_page_fault)
	exception(14)

ENTRY(exp_intel_reserved)
	exception(15)

ENTRY(exp_coprocessor_error)
	exception(16)

ENTRY(exp_alignment_check)
	exception(17)

ENTRY(exp_machine_check)
	exception(18)
		
ENTRY(exp_simd_coprocessor)
	exception(19)
		
ENTRY(intr0)
	intr(0x20)

ENTRY(intr1)
	intr(0x21)

ENTRY(intr2)
	intr(0x22)

ENTRY(intr3)
	intr(0x23)

ENTRY(intr4)
	intr(0x24)

ENTRY(intr5)
	intr(0x25)

ENTRY(intr6)
	intr(0x26)

ENTRY(intr7)
	intr(0x27)

ENTRY(intr8)
	intr(0x28)

ENTRY(intr9)
	intr(0x29)

ENTRY(intr10)
	intr(0x2a)

ENTRY(intr11)
	intr(0x2b)

ENTRY(intr12)
	intr(0x2c)

ENTRY(intr13)
	intr(0x2d)

ENTRY(intr14)
	intr(0x2e)	

ENTRY(intr15)
	intr(0x2f)

ENTRY(unknown_intr)
	intr(0xff)		

ENTRY(ext_exp)
	restore_context


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
