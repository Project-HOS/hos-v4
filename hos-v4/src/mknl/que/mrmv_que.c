/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*  �̥����ͥ� ���塼���                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������򥭥塼���鳰�� */
void mknl_rmv_que(
		T_MKNL_TCB *mtcb)	/* ���塼�����곰�������� */
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


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
