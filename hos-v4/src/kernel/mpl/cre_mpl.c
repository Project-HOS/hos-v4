/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* ����Ĺ����ס�������� */
ER cre_mpl(
		ID           mplid,		/* �����оݤβ���Ĺ����ס����ID�ֹ� */
		const T_CMPL *pk_cmpl)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ס��뤬��Ͽ��ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_MPLID_TO_MPLCB_RAM(mplid) != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif

	/* ����Ĺ����ס�������� */
	ercd = kernel_cre_mpl(mplid, pk_cmpl);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
