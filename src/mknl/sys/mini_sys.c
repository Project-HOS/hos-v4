/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル システム制御                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* グローバル変数宣言 */
STAT            mknl_ctx_stat;			/* システムのコンテキスト状態 */
T_MKNL_TCB      *mknl_run_mtcb = NULL;	/* 実行中タスクコントロールブロック */
T_HOSPAC_CTXINF mknl_idlctx;			/* アイドルループのコンテキスト */



/* μカーネルシステムの初期化 */
void mknl_ini_sys(void)
{
	/* プロセッサ抽象化コンポーネントの初期化 */
	hospac_ini_sys();
	
	/* アイドルタスク生成 */
	hospac_cre_ctx(&mknl_idlctx, 0, mknl_idl_loop, mknl_idl_stksz, mknl_idl_stk);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
