/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  μカーネル キュー操作                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク優先度順で追加 */
void mknl_adp_que(
		T_MKNL_QUE *que,	/* 追加するキュー */
		T_MKNL_TCB *mtcb)	/* 追加するタスク */
{
	T_MKNL_TCB *mtcb_head;
	T_MKNL_TCB *mtcb_tail;
	
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
		mtcb_head = que->head;
		mtcb_tail = mtcb_head->prev;
		do {
			/* キューを末尾から検索 */
			if ( mtcb->tskpri >= mtcb_tail->tskpri )
			{
				/* 自分より優先度が高いタスクがあればその後ろに挿入 */
				mtcb->next      = mtcb_tail;
				mtcb->prev      = mtcb_tail->prev;
				mtcb_tail->prev = mtcb;

				return;
			}
		} while ( mtcb_tail != mtcb_head );

		/* 自分より優先度が高いタスクが無ければ先頭に挿入 */
		mtcb->next      = mtcb_head;
		mtcb->prev      = mtcb_head->prev;
		mtcb_tail->prev = mtcb;
		que->head       = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
