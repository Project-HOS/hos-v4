/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*  �̥����ͥ� ���塼���                                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"



/* �������򥭥塼�������ɲ� */
void mknl_add_que(
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


/* �������򥭥塼���鳰�� */
void mknl_del_que(
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


/* ���塼�β�ž */
void mknl_rot_que(
		T_MKNL_QUE *que)	/* ��ž�����륭�塼 */
{
	if ( que->head != NULL )
	{
		que->head = que->head->next;
	}
}


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
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
