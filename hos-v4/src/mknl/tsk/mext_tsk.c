/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの終了 */
void mknl_ext_tsk(
				T_MKNL_TCB *mtcb)	/* 終了させるタスク */
{
	/* タイムアウトキューにあれば削除 */
	mknl_rmv_tmout(mtcb);		

	/* タスクキューから外す */
	if ( mtcb->que != NULL )
	{
		mknl_rmv_que(mtcb);
	}

	mtcb->tskstat = TTS_DMT;	/* 休止状態に設定 */
	mtcb->tskwait = 0;			/* 待ち要因クリア */

	/* 実行コンテキストの削除 */
	hospac_del_ctx(&mtcb->ctxinf);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
