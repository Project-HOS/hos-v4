/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* �����ϥ�ɥ������(ID�ֹ漫ư���դ�) */
ER_ID acre_cyc(
		const T_CCYC *pk_ccyc)	/* �����ϥ�ɥ�������������줿�ѥ��åȤؤΥݥ��� */
{
	ID cycid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ID�θ��� */
	for ( cycid = KERNEL_TMAX_CYCID; cycid >= KERNEL_TMIN_CYCID; cycid-- )
	{
		if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) == NULL )
		{
			break;
		}
	}
	if ( cycid < KERNEL_TMIN_CYCID )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOID;		/* ID�ֹ���­ */
	}
	
	/* �����ϥ�ɥ������ */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* ���顼ȯ�� */
	}

	return (ER_ID)cycid;		/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
