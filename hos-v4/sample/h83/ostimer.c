/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*    H8/3048 用 OSタイマ (ITU0を利用)                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"
#include "h8_3048.h"
#include "ostimer.h"



/* OSタイマの初期化 */
void OsTimer_Initialize(VP_INT exinf)
{
	/* ITU0 (システムタイマ）初期化 */
	TCR0   = 0x23;		/* φ/8でカウント */
	TSR0  &= 0xfe;		/* ステータスレジスタクリア */
	TIER0  = 0x01;		/* 割り込み許可 */
	GRA0   = 2000 - 1;	/* 1 msec のインターバル（16MHz時） */
	TSTR  |= 0x01;		/* TCNT0動作開始 */
}


/* タイマ用割り込みハンドラ */
void OsTimer_TimerHandler(VP_INT exinf)
{
	/* 割り込み要因クリア */
	TSR0 &= 0xfe;
	
	/* タイムティック供給 */
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
