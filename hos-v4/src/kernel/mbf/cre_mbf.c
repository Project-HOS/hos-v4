/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��å������Хåե�                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ��å������Хåե������� */
ER cre_mbf(
		ID           mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		const T_CMBF *pk_cmbf)	/* ��å������Хåե�������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ��å������Хåե�����Ͽ��ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( kernel_mbfcb_ram_tbl[mbfid - TMIN_MBFID] != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif

	/* ��å������Хåե������� */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
