/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                             */
/*  linker script for HOS-V4/IA32                                           */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
  . = 0x100000;
  _text = .;			/* Text and read-only data */
  .text : {
	*(.text)
	} = 0x9090
  .rodata : { *(.rodata) }
  _etext = .;			/* End of text section */

  .data : {			/* Data */
	*(.data)
	CONSTRUCTORS
	}

  _edata = .;			/* End of data section */
  __bss_start = .;		/* BSS */
  .bss : {
	*(.bss)
	}
  _end = . ;
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
