/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*  �̥����ͥ� ���塼���                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������򥭥塼�������ɲ� */
void mknl_adf_que(
		T_MKNL_QUE *que,	/* �ɲä��륭�塼 */
		T_MKNL_TCB *mtcb)	/* �ɲä��륿���� */
{
	T_MKNL_TCB *mtcb_head;
	T_MKNL_TCB *mtcb_tail;
	
	mtcb->que = que;
	if ( que->head == NULL )
	{
		/* ���塼�˥�������̵�������Ƭ������ */
		que->head  = mtcb;
		mtcb->next = mtcb;
		mtcb->prev = mtcb;
	}
	else
	{
		/* ���塼�������ɲ� */
		mtcb_head       = que->head;
		mtcb_tail       = mtcb_head->prev;
		mtcb->next      = mtcb_head;
		mtcb->prev      = mtcb_tail;
		mtcb_head->prev = mtcb;
		mtcb_tail->next = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
