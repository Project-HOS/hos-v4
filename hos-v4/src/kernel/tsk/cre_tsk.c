/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


/* ������������ */
ER cre_tsk(
		ID           tskid,		/* �����оݤΥ�����ID�ֹ� */
		const T_CTSK *pk_ctsk)	/* ������������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	if ( KERNEL_TSKID_TO_TCB_RAM(tskid) != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_ID;	/* ID�����ѤǤ��ʤ� */
	}
	
	/* ������������ */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
