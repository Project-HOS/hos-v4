/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
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
	if ( tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������Ͽ��ǽ�������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_TSKID_TO_TCB_RAM(tskid) != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif
	
	/* ������������ */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
