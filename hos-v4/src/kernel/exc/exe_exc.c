/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル CPU例外ハンドラ管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "knl_exc.h"



/* CPU例外ハンドラの開始 */
void kernel_sta_exc(void)
{
	/* 非タスク部(割り込みコンテキストに移行) */
	mknl_sta_ind();
}


/* CPU例外ハンドラの終了 */
void kernel_end_exc(void)
{
	/* タスク部に移行 */
	mknl_ext_ind();

	/* 遅延ディスパッチ実行 */
	mknl_dly_dsp();
}


/* CPU例外ハンドラみ処理実行 */
void kernel_exe_exc(
		EXCNO excno)		/* CPU例外ハンドラ番号 */
{
	T_KERNEL_EXCCB exccb;
	
	if ( excno < TMIN_EXCNO || excno > TMAX_EXCNO )
	{
		return;
	}
	
	exccb = kernel_exccb_tbl[excno];	/* ローカルにコピー */
	
	mknl_unl_sys();		/* 多重割り込み許可 */
	
	if ( exccb.exchdr != NULL )
	{
		exccb.exchdr();			/* CPU例外ハンドラ実行 */
	}
	
	mknl_loc_sys();		/* 多重割り込み禁止 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
