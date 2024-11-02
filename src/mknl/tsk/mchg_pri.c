/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク優先度変更 */
void mknl_chg_pri(
				T_MKNL_TCB *mtcb,	/* 優先度を変更するタスク */
				PRI tskpri)			/* 設定する優先度 */
{
	/* 優先度変更 */
	if ( !(mtcb->tskstat & TTS_WAI) )
	{
		/* 待ち状態でなければレディーキューに繋ぎなおす */
		mknl_rmv_que(mtcb);
		mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
	}
	mtcb->tskpri = tskpri;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
