/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル システム制御 システムタスク実行                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"


static void mknl_exe_sys_start(VP_INT exinf);	/* システムタスクの実行 */

static FP mknl_exe_sys_exec;					/* システム実行番地 */


/* システム実行  */
void mknl_exe_sys(
		FP     exec,
		VP_INT exinf)
{
	T_HOSPAC_CTXINF *ctxinf_run;
	
	/* 実行中コンテキストの退避 */
	ctxinf_run = &mknl_run_mtcb->ctxinf;
	
	/* システム実行番地保存 */
	mknl_exe_sys_exec = exec;
	
	/* アイドルコンテキストをシステムタスクとして一時利用 */
	hospac_del_ctx(&mknl_idlctx);												/* アイドルコンテキストを破棄 */
	hospac_cre_ctx(&mknl_idlctx, exinf, exec, mknl_idl_stksz, mknl_idl_stk);	/* アイドルタスク生成 */
	
	/* タスクコンテキストスイッチ実行 */
	mknl_run_mtcb = NULL;
	hospac_swi_ctx(ctxinf_run, &mknl_idlctx);
}


/* システムタスクの実行 */
void mknl_exe_sys_start(VP_INT exinf)
{
	/* システムタスクで実行 */
	mknl_exe_sys_exec(exinf);
	
	/* 完了後アイドルに戻る */
	mknl_idl_loop();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
