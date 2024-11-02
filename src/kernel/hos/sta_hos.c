/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    システム                                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_hos.h"
#include "knl_int.h"
#include "knl_tim.h"



/* HOS カーネル動作開始 */
ER sta_hos(void)
{
	/* コンフィギュレーター変数の初期化 */
	kernel_cfg_init();

	/* カーネルの初期化 */
	mknl_ini_sys();		/* μカーネルシステムの初期化 */
	
	/* 擬似的に割り込みハンドラと見なす */
	kernel_int_cnt = 1;

	/* スタートアップ用コンテキストに移行 */
	mknl_sta_startup();
	
	/* 初期化 */
	kernel_ini_tim();	/* 時間管理機能の初期化 */
	kernel_cfg_start();	/* コンフィギュレーションの初期化 */
	
	/* 割り込みネスト回数クリア */
	kernel_int_cnt = 0;

	/* カーネル動作状態へ移行 */
	mknl_ext_startup();

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
