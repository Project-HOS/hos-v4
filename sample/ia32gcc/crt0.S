/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#define ASM	1
#define GRUB_HEADER_MAGIC	0x1BADB002
#define GRUB_HEADER_FLAGS	0x00010001
#define BOOT_STK_SIZ		0x1000
#define EXT_C(sym)              sym

.text
	.globl	start, _start, _edata
.org 0
start:
_start:
	jmp	__boot_entry
/*
 *	Multiboot compliant header
 *      This should be aligned 4 byte boundary.
 */
	.align	4 
__grub_multiboot_header: /*  Header for multiboot kernel */
	.long	GRUB_HEADER_MAGIC 	/* magic */
	.long	GRUB_HEADER_FLAGS       /* flags */
	 /* checksum */
	.long	-(GRUB_HEADER_MAGIC + GRUB_HEADER_FLAGS)
	.long	__grub_multiboot_header	/* header_addr */
	.long	_start                 	/* load_addr */
	.long	_edata                 	/* load_end_addr */
	.long	_end                    /* bss_end_addr */
	.long	__boot_entry            /* entry_addr */

__boot_entry:
	movl %cr0,%ecx
	andl $0x7fffffff,%ecx
	xorl  $8,%ecx   /*  disable fpu not available exception  */
	movl %ecx,%cr0
	/* Prepare the kernel's initial stack.  */
	movl	$(__kernel_ini_stk + BOOT_STK_SIZ), %esp
	pushl	$0  /* Clear EFLAGS.  */
	popf
	/* Push the pointer to the Multiboot information structure.  */
	pushl	%ebx
	pushl	%eax                /* Push the magic value.  */
	call	EXT_C(sta_hos)      /* Now enter kernel  */
	pushl	$halt_msg           /* Halt message(It' prepared for safe.)  */
	call	EXT_C(printk)

	cli	
errloop:
	hlt
	jmp	errloop

halt_msg:
	.asciz	"System is halted(Somethig wrong)."
	/* Our stack area.  */
	.comm	__kernel_ini_stk, BOOT_STK_SIZ
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
