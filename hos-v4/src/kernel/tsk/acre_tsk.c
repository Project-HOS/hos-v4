/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


/* ������������(ID�ֹ漫ư���դ�) */
ER_ID acre_tsk(
		const T_CTSK *pk_ctsk)	/* ������������������줿�ѥ��åȤؤΥݥ��� */
{
	ID tskid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ID�θ��� */
	for ( tskid = kernel_tcb_cnt; tskid >= TMIN_TSKID; tskid++ )
	{
		if ( KERNEL_TSKID_TO_TCB_RAM(tskid) == NULL )
		{
			break;
		}
	}
	if ( tskid < TMIN_TSKID )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOID;		/* ID�ֹ���­ */
	}
	
	/* ������������ */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* ���顼ȯ�� */
	}

	return (ER_ID)tskid;		/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
