/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ��ǥ������塼��Ƭ�Υ�������õ�� */
T_MKNL_TCB* mknl_srh_top(void)
{
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_head;
	INT i;

	/* �ǹ�ͥ���٤μ¹Բ�ǽ��������õ�� */
	for ( i = 0; i < mknl_rdq_cnt; i++ )	/* ͥ���٤ι⤤���塼�����˸��� */
	{
		if ( mknl_rdq_tbl[i].head != NULL )
		{
			/* �����Ԥ����֤�̵����Ƭ��������õ�� */
			mtcb_head = mknl_rdq_tbl[i].head;
			mtcb      = mtcb_head;
			do
			{
				if ( !(mtcb->tskstat & TTS_SUS) )
				{
					return mtcb;	/* ���Ĥ������������֤� */
				}
				mtcb = mtcb->next;
			} while ( mtcb != mtcb_head);
		}
	}

	return NULL;	/* �¹Բ�ǽ������̵�� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
