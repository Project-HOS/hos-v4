/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  μカーネル キュー操作                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク優先度順で追加 */
void mknl_adp_que(
		T_MKNL_QUE *que,	/* 追加するキュー */
		T_MKNL_TCB *mtcb)	/* 追加するタスク */
{
	T_MKNL_TCB *mtcb_next;
	T_MKNL_TCB *mtcb_prev;
	
	mtcb->que = que;
	if ( que->head == NULL )
	{
		/* キューにタスクが無ければ先頭に設定 */
		que->head  = mtcb;
		mtcb->next = mtcb;
		mtcb->prev = mtcb;
	}
	else
	{
		/* 挿入位置をキューを先頭から検索 */
		mtcb_next = que->head;
		do {
			/* 自分より低優先のタスクがあれば挿入位置検出完了 */
			if ( mtcb_next->tskpri > mtcb->tskpri )
			{
				if ( mtcb_next == que->head )	/* 挿入位置が先頭なら */
				{
					mtcb_prev = mtcb_next->prev;
					que->head = mtcb;
				}
				break;
			}

			/* 次に進む */
			mtcb_prev = mtcb_next;
			mtcb_next = mtcb_next->next;
		} while ( mtcb_next != que->head );
		
		/* タスクをキューに挿入 */
		mtcb->next      = mtcb_next;
		mtcb->prev      = mtcb_prev;
		mtcb_next->prev = mtcb;
		mtcb_prev->next = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
