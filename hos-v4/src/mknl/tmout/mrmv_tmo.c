/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タイムアウト待ち行列からタスクを取り除く */
void mknl_rmv_tmout(
		T_MKNL_TCB *mtcb)	/* 待ち行列から削除するタスク */
{
	/* タイムアウトキューに未接続なら無視 */
	if ( mtcb->tm_prev == NULL )
	{
		return;
	}

	/* キューの最後の１つタスクなら */
	if ( mtcb->tm_next == mtcb )
	{
		mknl_timout_head = NULL;	/* タイムアウトキューを空にする */
	}
	else
	{
		/* 末尾でなければ */
		if ( mtcb != mknl_timout_head->tm_prev )
		{
			/* 時間差分を清算 */
			mtcb->tm_next->diftim += mtcb->diftim;
		}
	
		/* 先頭なら */
		if ( mtcb == mknl_timout_head )
		{
			mknl_timout_head = mtcb->tm_next;	/* 先頭位置更新 */
		}
		
		/* キューから外す */
		mtcb->tm_next->tm_prev = mtcb->tm_prev;
		mtcb->tm_prev->tm_next = mtcb->tm_next;
	}
	
	/* 未接続に設定 */
	mtcb->tm_prev = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
