/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* ����Ĺ����ס�������� */
ER cre_mpf(
		ID           mpfid,		/* �����оݤθ���Ĺ����ס����ID�ֹ� */
		const T_CMPF *pk_cmpf)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ID�����Ѳ�ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID] == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_ID;	/* ����ID */
	}
#endif

	/* ����Ĺ����ס�������� */
	ercd = kernel_cre_mpf(mpfid, pk_cmpf);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
