/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
