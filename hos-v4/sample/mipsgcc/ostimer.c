/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*  OS タイマ                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "semb1200a/ux_signal.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ostimer.h"

// CPUクロックの1/2でカウント
// 300000 / (600000000 / 2) = 0.001
// 600MHzの場合、1ms = 300000
#define COMPARE  (300000)

/* OS用タイマ初期化 */
void ostim_init(VP_INT exinf)
{
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
	SET_CP0_STATUS (IE_IRQ5);
}

/* OSタイマ用ハンドラ */
void ostim_hdr(VP_INT exinf)
{
    /* カウンタレジスタのクリア */
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
    /* タイムティックの供給 */
    isig_tim();
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
