/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タイムアウト待ち行列にタスクを追加 */
ER mknl_add_tmout(
		T_MKNL_TCB *mtcb,	/* 待ち行列に加えるタスク */
		RELTIM     tmout)	/* タイムアウトまでの時間 */
{
	T_MKNL_TCB* mtcb_tmp;

	/* 最初の１つなら */
	if ( mknl_timout_head == NULL )
	{
		/* 最初の１つをキューに登録 */
		mtcb->tm_next    = mtcb;
		mtcb->tm_prev    = mtcb;
		mknl_timout_head = mtcb;

		/* タイムアウト時刻を設定 */
		mtcb->diftim = tmout;

		return E_OK;
	}
	
	/* 挿入場所を検索 */
	mtcb_tmp = mknl_timout_head;
	do
	{	
		/* 時間比較 */
		if ( tmout < mtcb_tmp->diftim )
		{
			/* 時間の差分を設定 */
			mtcb_tmp->diftim -= tmout;
			mtcb->diftim      = tmout;

			/* リストに挿入 */
			mtcb->tm_next          = mtcb_tmp;
			mtcb->tm_prev          = mtcb_tmp->tm_prev;
			mtcb->tm_next->tm_prev = mtcb;
			mtcb->tm_prev->tm_next = mtcb;
			
			/* 先頭なら */
			if ( mtcb_tmp == mknl_timout_head )
			{
				mknl_timout_head = mtcb;	/* 先頭ポインタ更新 */
			}
			
			return E_OK;
		}
		
		tmout -= mtcb_tmp->diftim;		/* 差分を減算 */
		
		mtcb_tmp = mtcb_tmp->tm_next;	/* 次のTCBへ進む */
	} while ( mtcb_tmp != mknl_timout_head->tm_prev );	/* リストを一周するまでループ */
	
	/* 末尾に追加 */
	mtcb->tm_next          = mtcb_tmp->tm_next;
	mtcb->tm_prev          = mtcb_tmp;
	mtcb->tm_next->tm_prev = mtcb;
	mtcb->tm_prev->tm_next = mtcb;

	/* 残った差分を設定 */
	mtcb->diftim = tmout;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
