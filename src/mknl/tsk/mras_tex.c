/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク例外処理の要求 */
void mknl_ras_tex(
		T_MKNL_TCB *mtcb)	/* 例外処理を要求するタスク */
{
	if ( mtcb == mknl_run_mtcb && !(mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* 実行中タスクで、例外禁止でなければ例外発行 */
		do
		{
			mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mtcb->texstat != 0 );	/* 例外要因がなくなるまでループ */
	}
	else
	{
		/* 例外を保留する */
		mtcb->texstat &= MKNL_TTS_RDLY;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
