/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
		if ( mknl_rdq_tbl[i].head != NULL )
		{
			/* 強制待ち状態で無い先頭タスクを探す */
			mtcb_head = mknl_rdq_tbl[i].head;
			mtcb      = mtcb_head;
			do
			{
				if ( !(mtcb->tskstat & TTS_SUS) )
				{
					return mtcb;	/* 見つけたタスクを返す */
				}
				mtcb = mtcb->next;
			} while ( mtcb != mtcb_head);
		}
	}

	return NULL;	/* 実行可能タスク無し */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
