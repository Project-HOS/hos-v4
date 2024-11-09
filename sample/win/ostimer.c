/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   タイムティック提供                                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "ostimer.h"
#include "wintimer.h"



/* 初期化 */
void OsTimer_Initialize(VP_INT exinf)
{
	WinTimer_Initialize(0);
}


/* タイマ割り込みハンドラ */
void OsTimer_Handler(VP_INT exinf)
{
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
