/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* ������������ */
ER cre_cyc(
		ID           cycid,		/* �����оݤμ����ϥ�ɥ��ID�ֹ� */
		const T_CCYC *pk_ccyc)	/* �����ϥ�ɥ�������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������Ͽ��ǽ�������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif
	
	/* ������������ */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
