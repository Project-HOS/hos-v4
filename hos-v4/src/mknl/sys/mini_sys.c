/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル システム制御                                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* グローバル変数宣言 */
STAT            mknl_ctx_stat;			/* システムのコンテキスト状態 */
T_MKNL_TCB      *mknl_run_mtcb = NULL;	/* 実行中タスクコントロールブロック */
T_HOSPAC_CTXINF mknl_idlctx;			/* アイドルループのコンテキスト */



/* μカーネルシステムの初期化 */
void mknl_ini_sys(void)
{
	hospac_ini_sys();					/* プロセッサ抽象化コンポーネントの初期化 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
