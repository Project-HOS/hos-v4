/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (Windows用)                            */
/*    割り込み処理                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 擬似割り込みのエミュレート(ITRONタスクとは無関係のスレッドから呼ぶこと) */
void hospac_win_int(INTNO intno)
{
	T_HOSPAC_CTXINF *ctxinf;

	/* 範囲チェック */
	if ( intno < KERNEL_TMIN_INTNO || intno > KERNEL_TMAX_INTNO )
	{
		return;
	}

	/* セマフォを取る */
	WaitForSingleObject(hospac_hSem, INFINITE);

	/* 実行中スレッドをサスペンドする */
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}
	SuspendThread(ctxinf->hThread);
	ctxinf->blIntSuspend = TRUE;

	/* 割り込みフラグセット */
	hospac_blInt = TRUE;

	/* 非タスク部(割り込みコンテキストに移行) */
	mknl_sta_ind();
	
	/* 割り込みの実行 */
	if ( kernel_intcb_tbl[intno].isr != NULL )
	{
		kernel_intcb_tbl[intno].isr(kernel_intcb_tbl[intno].exinf);			/* 割り込みサービスルーチン実行 */
	}

	/* タスク部に移行 */
	mknl_ext_ind();

	/* 割り込みフラグクリア */
	hospac_blInt = FALSE;

	/* 遅延フラグクリア */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* 最高優先度の実行可能タスクを探す */
	mknl_run_mtcb = mknl_srh_top();
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}

	/* セマフォを返却 */
	if ( ctxinf->blIntSuspend )
	{
		ctxinf->blIntSuspend = FALSE;
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}

	/* 実行中スレッドの復帰 */
	ResumeThread(ctxinf->hThread);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
