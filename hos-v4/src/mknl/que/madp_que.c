/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*  �̥����ͥ� ���塼���                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ������ͥ���ٽ���ɲ� */
void mknl_adp_que(
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
		mtcb_head = que->head;
		mtcb_tail = mtcb_head->prev;
		do {
			/* ���塼���������鸡�� */
			if ( mtcb->tskpri >= mtcb_tail->tskpri )
			{
				/* ��ʬ���ͥ���٤��⤤������������Ф��θ������� */
				mtcb->next      = mtcb_tail;
				mtcb->prev      = mtcb_tail->prev;
				mtcb_tail->prev = mtcb;

				return;
			}
		} while ( mtcb_tail != mtcb_head );

		/* ��ʬ���ͥ���٤��⤤��������̵�������Ƭ������ */
		mtcb->next      = mtcb_head;
		mtcb->prev      = mtcb_head->prev;
		mtcb_tail->prev = mtcb;
		que->head       = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
