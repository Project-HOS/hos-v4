/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの強制待ち */
void mknl_sus_tsk(
		T_MKNL_TCB *mtcb)	/* 強制待ち状態にするタスク */
{
	/* タスクの強制待ち(レディーキューからは外さない) */
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_WAS;
	}
	else
	{
		mtcb->tskstat = TTS_SUS;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
