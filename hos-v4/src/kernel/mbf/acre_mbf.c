/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��å������Хåե�                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ��å������Хåե�������(ID�ֹ漫ư���դ�) */
ER_ID acre_mbf(
		const T_CMBF *pk_cmbf)	/* ��å������Хåե�������������줿�ѥ��åȤؤΥݥ��� */
{
	ID mbfid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( mbfid = KERNEL_TMAX_MBFID; mbfid >= KERNEL_TMIN_MBFID; mbfid-- )
	{
		if ( kernel_mbfcb_ram_tbl[mbfid - KERNEL_TMIN_MBFID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( mbfid < KERNEL_TMIN_MBFID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* ��å������Хåե������� */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)mbfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
