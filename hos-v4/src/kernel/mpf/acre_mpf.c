/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* ����Ĺ����ס��������(ID�ֹ漫ư���դ�) */
ER_ID acre_mpf(
		const T_CMPF *pk_cmpf)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	ID mpfid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( mpfid = KERNEL_TMAX_MPFID; mpfid >= TMIN_MPFID; mpfid-- )
	{
		if ( kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( mpfid < TMIN_MPFID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* ����Ĺ����ס�������� */
	ercd = kernel_cre_mpf(mpfid, pk_cmpf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)mpfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
