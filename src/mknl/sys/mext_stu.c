/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル システム制御                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* スタートアップルーチンの終了処理 */
void mknl_ext_startup(void)
{
	T_HOSPAC_CTXINF dmy_ctx;
	T_MKNL_TCB      *mtcb;
	
	mknl_ctx_stat = MKNL_TSS_TSK;	/* タスク部に設定 */
	
	/* 最高優先度の実行可能タスクを探す */
	mtcb = mknl_srh_top();
	
	/* この関数を呼び出したコンテキストをアイドルタスクとして処理開始 */
	if ( mtcb != NULL )
	{
		mknl_run_mtcb = mtcb;
		hospac_swi_ctx(&dmy_ctx, &mtcb->ctxinf);	/* タスクを開始 */
	}
	else
	{
		mknl_run_mtcb = NULL;
		hospac_swi_ctx(&dmy_ctx, &mknl_idlctx);		/* アイドルコンテキスト登録のみ */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
