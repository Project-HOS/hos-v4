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


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
