/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル システム制御                                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"
#include "kernel.h"


/* グローバル変数宣言 */
STAT            mknl_ctx_stat;			/* システムのコンテキスト状態 */
T_MKNL_TCB      *mknl_run_mtcb = NULL;	/* 実行中タスクコントロールブロック */
T_HOSPAC_CTXINF mknl_idlctx;			/* アイドルループのコンテキスト */


/* μカーネルシステムの初期化 */
void mknl_ini_sys(void)
{
	hospac_ini_sys();					/* プロセッサ抽象化コンポーネントの初期化 */
}



/* スタートアップルーチンの開始処理 */
void mknl_sta_startup(void)
{
	mknl_ctx_stat = TSS_INDP | TSS_DINT;	/* 割り込み禁止でタスク独立部に設定 */
}


/* スタートアップルーチンの終了処理 */
void mknl_ext_startup(void)
{						
	T_MKNL_TCB *mtcb;

	mknl_ctx_stat = TSS_TSK;	/* タスク部に設定 */

	/* 最高優先度の実行可能タスクを探す */
	mtcb = mknl_srh_top();

	/* この関数を呼び出したコンテキストをアイドルタスクとして処理開始 */
	if ( mtcb != NULL )
	{
		mknl_run_mtcb = mtcb;
		hospac_swi_ctx(&mknl_idlctx, &mtcb->ctxinf);	/* タスクを開始 */
		mknl_run_mtcb = NULL;
	}
	else
	{
		mknl_run_mtcb = NULL;
		hospac_swi_ctx(&mknl_idlctx, &mknl_idlctx);		/* アイドルコンテキスト登録のみ */
	}

	hospac_ena_int();	/* 割り込みの許可 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
