/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  μカーネル キュー操作                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* キューをクリア */
void mknl_clr_que(
		T_MKNL_QUE *que)	/* クリアするキュー */
{
	T_MKNL_TCB *mtcb;

	/* 待ちタスクの解除 */
	while (	(mtcb = mknl_ref_qhd(que)) != NULL )
	{
		mknl_rmv_que(mtcb);			/* イベントフラグの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);		/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, E_DLT);	/* タスクの待ち解除 */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
