/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* グローバル変数 */
T_MKNL_TCB *mknl_timout_head;		/* タイムアウトキューの先頭 */



/* タイムアウトにタイムティック供給 */
void mknl_tic_tmout(
		RELTIM tictim)		/* 追加するタイムティック */
{
	register T_MKNL_TCB *mtcb;

	/* ローカルにコピー */
	mtcb = mknl_timout_head;

	/* タイムアウトキューが空ならリターン */
	if ( mtcb == NULL )
	{
		return;
	}

	/* タイムアウトキューの処理 */
	for ( ; ; )
	{
		/* タイムアウトに達しないなら */
		if ( tictim < mtcb->diftim )
		{
			mtcb->diftim -= tictim;		/* タイムアウト時間を減算 */
			break;
		}
		
		tictim -= mtcb->diftim;			/* タイムティックを減算 */
		
		mknl_wup_tsk(mtcb, E_TMOUT);	/* タイムアウト起床 */
		mknl_exe_dsp();					/* 遅延ディスパッチ予約を行う */
		
		/* キューから外す */
		if ( mtcb->tm_next == mtcb )	/* 最後の１つなら */
		{
			/* キューを空にする */
			mtcb->tm_prev = NULL;
			mtcb          = NULL;
			break;
		}
		else
		{
			/* キューから取り外す */
			mtcb->tm_next->tm_prev = mtcb->tm_prev;
			mtcb->tm_prev->tm_next = mtcb->tm_next;
			mtcb->tm_prev = NULL;
			mtcb = mtcb->tm_next;
		}

		/* ここで一度、多重割り込みの機会を与える */
		mknl_unl_sys();		/* システムのロック解除 */
		mknl_loc_sys();		/* システムのロック */
	}
	
	/* メモリに書き戻す */
	mknl_timout_head = mtcb;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
