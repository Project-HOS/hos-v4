/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク例外処理の実行 */
void mknl_exe_tex(void)
{
	/* 非タスクコンテキストなら何もしない */
	if ( mknl_ctx_stat & MKNL_TSS_INDP )
	{
		return;
	}

	if (  (mknl_run_mtcb->texstat & MKNL_TTS_RDLY)
				&& !(mknl_run_mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* 例外保留があり、例外禁止でなければ例外発行 */
		do
		{
			mknl_run_mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mknl_run_mtcb->texstat != 0 );	/* 例外要因がなくなるまでループ */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
