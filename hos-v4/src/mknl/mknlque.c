/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*  μカーネル キュー操作                                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"



/* タスクをキュー末尾に追加 */
void mknl_add_que(
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
		/* キュー末尾に追加 */
		mtcb_head       = que->head;
		mtcb_tail       = mtcb_head->prev;
		mtcb->next      = mtcb_head;
		mtcb->prev      = mtcb_tail;
		mtcb_head->prev = mtcb;
		mtcb_tail->next = mtcb;
	}
}


/* タスクをキューから外す */
void mknl_del_que(
		T_MKNL_TCB *mtcb)	/* キューから取り外すタスク */
{
	T_MKNL_QUE *que;
	T_MKNL_TCB *mtcb_next;
	T_MKNL_TCB *mtcb_prev;

	que = mtcb->que;

	if ( que == NULL )
	{
		return;
	}

	if ( mtcb->next != mtcb )
	{
		mtcb_next = mtcb->next;
		mtcb_prev = mtcb->prev;
		mtcb_next->prev = mtcb_prev;
		mtcb_prev->next = mtcb_next;
		if ( que->head == mtcb )
		{
			que->head = mtcb_next;
		}
	}
	else
	{
		que->head = NULL;
	}
	mtcb->que = NULL;
}


/* キューの回転 */
void mknl_rot_que(
		T_MKNL_QUE *que)	/* 回転させるキュー */
{
	if ( que->head != NULL )
	{
		que->head = que->head->next;
	}
}


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
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
