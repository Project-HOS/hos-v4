/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include "itron.h"
#include "printk.h"
/*
 *  例外ハンドラ定義マクロ
 */
#define def_exp_hdr(no,str,name)        \
void exp_hdr_##name(VP_INT exinf)         \
{                                       \
  printk("An exception occurs(" str ")"); \
  __asm__ __volatile__("cli\n\t") ;     \
  while(1);                             \
}                                       
/*
 *  例外ハンドラ定義
 */
def_exp_hdr(0,"Zero divided",zero_div)
def_exp_hdr(1,"Hardware debug",hwdebug)
def_exp_hdr(2,"NMI",nmi)
def_exp_hdr(3,"debug",debug)
def_exp_hdr( 4, "overflow", overflow)
def_exp_hdr( 5, "bounds", bounds)
def_exp_hdr( 6, "invalid operand", invalid_op)
def_exp_hdr( 7, "device not available", device_not_available)
def_exp_hdr( 8, "double fault", double_fault)
def_exp_hdr( 9, "coprocessor segment overrun", coprocessor_segment_overrun)
def_exp_hdr(10, "invalid TSS", invalid_TSS)
def_exp_hdr(11, "segment not present", segment_not_present)
def_exp_hdr(12, "stack segment", stack_segment)
def_exp_hdr(13, "general protection", genprot)
def_exp_hdr(14, "page fault", pg_fault)
def_exp_hdr(16, "coprocessor", copro_fault)
def_exp_hdr(17, "alignment check", alignment)
def_exp_hdr(18, "machine check", machine_check)

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
