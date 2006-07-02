/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* ����Ĺ����ס��������(ID�ֹ漫ư���դ�) */
ER_ID acre_mpl(
		const T_CMPL *pk_cmpl)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	ID mplid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( mplid = KERNEL_TMAX_MPLID; mplid >= KERNEL_TMIN_MPLID; mplid-- )
	{
		if ( KERNEL_MPLID_TO_MPLCB_RAM(mplid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( mplid < KERNEL_TMIN_MPLID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* ����Ĺ����ס�������� */
	ercd = kernel_cre_mpl(mplid, pk_cmpl);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)mplid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
