/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* レディーキュー先頭のタスクを探す */
T_MKNL_TCB* mknl_srh_top(void)
{
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_head;
	INT i;

	/* 最高優先度の実行可能タスクを探す */
	for ( i = 0; i < mknl_rdq_cnt; i++ )	/* 優先度の高いキューから順に検索 */
	{
		if ( mknl_rdq_tbl[i].head != NULL )	/* レディキューには実行可能タスクしかない */
		{
			return mknl_rdq_tbl[i].head;
		}
	}

	return NULL;	/* 実行可能タスク無し */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
