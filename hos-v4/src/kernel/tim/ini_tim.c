/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    システム時間管理                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* システム時間管理用変数 */
SYSTIM kernel_systim;			/* システム時刻 */
UW     kernel_tic_cnt = 0;		/* タイムティック用カウンタ */



/* 時間管理機能の初期化 */
void kernel_ini_tim(void)
{
	kernel_tic_cnt = kernel_tic_deno;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
