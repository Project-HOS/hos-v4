/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*  �̥����ͥ� ���塼���                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ������ͥ���ٽ���ɲ� */
void mknl_adp_que(
		T_MKNL_QUE *que,	/* �ɲä��륭�塼 */
		T_MKNL_TCB *mtcb)	/* �ɲä��륿���� */
{
	T_MKNL_TCB *mtcb_next;
	T_MKNL_TCB *mtcb_prev;
	
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
		/* �������֤򥭥塼����Ƭ���鸡�� */
		mtcb_next = que->head;
		do {
			/* ��ʬ�����ͥ��Υ�������������������ָ��д�λ */
			if ( mtcb_next->tskpri > mtcb->tskpri )
			{
				if ( mtcb_next == que->head )	/* �������֤���Ƭ�ʤ� */
				{
					mtcb_prev = mtcb_next->prev;
					que->head = mtcb;
				}
				break;
			}

			/* ���˿ʤ� */
			mtcb_prev = mtcb_next;
			mtcb_next = mtcb_next->next;
		} while ( mtcb_next != que->head );
		
		/* �������򥭥塼������ */
		mtcb->next      = mtcb_next;
		mtcb->prev      = mtcb_prev;
		mtcb_next->prev = mtcb;
		mtcb_prev->next = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
