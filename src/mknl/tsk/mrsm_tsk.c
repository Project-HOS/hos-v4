/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの強制待ち解除 */
void mknl_rsm_tsk(
		T_MKNL_TCB *mtcb)	/* 強制待ち解除するタスク */
{
	/* 強制待ち解除 */
	if ( mtcb->tskstat == TTS_WAS )
	{
		mtcb->tskstat = TTS_WAI;		/* 二重待ち状態なら待ち状態 */
	}
	else
	{
		mtcb->tskstat = TTS_RDY;		/* 強制待ち状態なら実行可能状態 */
		mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
