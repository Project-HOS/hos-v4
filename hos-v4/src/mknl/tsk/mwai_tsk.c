/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの待ち設定 */
void mknl_wai_tsk(
		T_MKNL_TCB *mtcb,		/* 待ち状態にするタスク */
		STAT        tskwait)	/* 待ち要因 */
{
	/* 待ち状態に設定 */
	mknl_rmv_que(mtcb);		/* レディーキューから外す */
	mtcb->tskstat = TTS_WAI;
	mtcb->tskwait = tskwait;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
