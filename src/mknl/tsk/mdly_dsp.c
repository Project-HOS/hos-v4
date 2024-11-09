/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* 遅延していたディスパッチの実行 */
void mknl_dly_dsp(void)
{
	/* システムコンテキストチェック */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT) )
	{
		return;		/* ディスパッチ実行可能でなければ保留続行 */
	}

	/* 遅延フラグチェック */
	if ( !(mknl_ctx_stat & MKNL_TSS_DDLY) )
	{
		return;		/* 遅延が無ければ何もしない */
	}

	/* 遅延フラグクリア */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* 遅延ディスパッチ実行 */
	mknl_exe_dsp();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
