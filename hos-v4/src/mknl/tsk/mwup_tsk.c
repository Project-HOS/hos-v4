/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの待ち解除 */
void mknl_wup_tsk(
		T_MKNL_TCB *mtcb,	/* スリープ解除するタスク */
		ER_UINT    ercd)	/* 解除するタスクに渡すエラーコード */
{
	/* タスクのスリープ解除 */
	mtcb->ercd = ercd;
	mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_RDY;	/* 待ち解除なら実行可能状態 */
	}
	else
	{
		mtcb->tskstat = TTS_SUS;	/* 二重待ち状態なら強制待ち状態 */
	}
	mtcb->tskwait = 0;		/* 待ち要因クリア */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
