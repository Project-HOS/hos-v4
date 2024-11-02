/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   OS用タイマ                                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "sh7045.h"
#include "ostimer.h"



/* OS用タイマ初期化 */
void ostim_init(VP_INT exinf)
{
	/* タイマ初期化 */
	*SH_CMCSR0 = 0x0040;
	*SH_CMCOR0 = (UH)(INT)exinf;
	*SH_CMSTR  = 0x0001;
	*SH_IPRG   = 0x00f0;
}


/* 割り込みハンドラサンプル */
void ostim_hdr(VP_INT exinf)	/* OSタイマ用ハンドラ */
{
	*SH_CMCSR0 &= 0xff7f;
	
	isig_tim();		/* タイムティックの供給 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
