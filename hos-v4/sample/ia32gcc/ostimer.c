/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                             */
/*  IA32 OS タイマ                                                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "ia32/ioport.h"
#include "ostimer.h"
/* OS用タイマ初期化 */
void ostim_init(VP_INT exinf)
{
  unsigned short divisor;

  /* 周期タイマの設定  */
#if PERIOD<1000
    divisor=PIT_I8254_INPFREQ / (1000 * 1000) * PERIOD + 1;
#else
    divisor=PIT_I8254_INPFREQ / (1000 / (PERIOD/1000)) + 1;
#endif

  /*  Set timer Channel2 as rate Genarator  */
  out_port_byte(PIT_PORT_MODECNTL, 0x34);
  /*
   *  Set interval as period_us  
   */
  out_port_byte(PIT_PORT_CHANNEL0, (divisor&(0xff)));      /*  write LSB  */
  out_port_byte(PIT_PORT_CHANNEL0, ((divisor>>8)&(0xff))); /*  write MSB  */
  
  return ;
}


/* 割り込みハンドラサンプル */
void ostim_hdr(VP_INT exinf)	/* OSタイマ用ハンドラ */
{
  isig_tim();		/* タイムティックの供給 */
}
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
