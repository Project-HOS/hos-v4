/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"
#include "dsp_hok.h"



/* タスクディスパッチの実行 */
ER_UINT mknl_exe_dsp(void)
{
	T_HOSPAC_CTXINF *ctxinf_top;
	T_HOSPAC_CTXINF *ctxinf_run;
	T_MKNL_TCB *mtcb_top;
	T_MKNL_TCB *mtcb_run;

	/* コンテキストチェック */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT) )
	{
		/* ディスパッチ実行可能状態で無ければ保留する */
		mknl_ctx_stat |= MKNL_TSS_DDLY;	/* ディスパッチ遅延フラグをセット */
		return E_OK;
	}

	/* 最高優先度の実行可能タスクを探す */
	mtcb_top = mknl_srh_top();

	mtcb_run = mknl_run_mtcb;	/* 現在のタスクをローカルに退避 */

	/* 実行中タスクが同じなら何もしない(アイドルからアイドルも含む） */
	if ( mtcb_top == mtcb_run )
	{
		if ( mtcb_run == NULL )
		{
			return E_OK;
		}
		return mtcb_run->ercd;
	}

	/* アイドルタスク実行中でないかチェック */
	if ( mtcb_run == NULL )
	{
		/* アイドルならアイドルコンテキストを設定 */
		ctxinf_run = &mknl_idlctx;
	}
	else
	{
		/* 実行中のコンテキストを設定 */
		ctxinf_run = &mtcb_run->ctxinf;
	}

	/* 次に実行するタスクがあるかどうかチェック */
	if ( mtcb_top == NULL )
	{
		/* 実行先が無ければアイドルコンテキストを設定 */
		mknl_run_mtcb = NULL;
		ctxinf_top    = &mknl_idlctx;
	}
	else
	{
		/* 実行先のタスクを実行中タスクとして登録 */
		mknl_run_mtcb     = mtcb_top;
		mtcb_top->tskstat = TTS_RDY;
		
		/* 実行先のコンテキストを設定 */
		ctxinf_top = &mtcb_top->ctxinf;
	}

	/* タスクコンテキストスイッチ実行 */
	hospac_swi_ctx(ctxinf_run, ctxinf_top);

	_HOS_TSW_HOK();		/* コンテキストスイッチのフック */

	if ( mtcb_run == NULL )
	{
		return E_OK;
	}

	return mtcb_run->ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
