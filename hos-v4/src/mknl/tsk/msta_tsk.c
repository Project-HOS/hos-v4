/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクの開始 */
void mknl_sta_tsk(
		T_MKNL_TCB *mtcb,					/* μカーネルタスクコントロールブロック */
		VP_INT     exinf,					/* タスクの拡張情報 */
		FP         task,					/* タスクの起動番地 */
		PRI        tskpri,					/* タスクの起動時優先度 */
		SIZE       stksz,					/* タスクのスタック領域のサイズ */
		VP         stk)						/* タスクのスタック領域の先頭番地 */
{
	/* 実行コンテキストの作成 */
	mtcb->data = exinf;
	hospac_cre_ctx(&mtcb->ctxinf, exinf, task, stksz, stk);

	/* タスクの状態設定 */
	mtcb->tskstat = TTS_RDY;	/* レディー状態に設定 */
	mtcb->texstat = 0;			/* 例外状態初期化 */
	mtcb->tskpri  = tskpri;		/* 優先度設定 */
	mtcb->tskwait = 0;			/* 待ち要因初期化 */

	/* レディーキューに設定 */
	mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
