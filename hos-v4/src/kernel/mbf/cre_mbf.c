/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ��å������Хåե�                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
	if ( mbfid < TMIN_MBFID || mbfid > TMAX_MBFID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ��å� */

	/* ID�����Ѳ�ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_mbfcb_ram_tbl[mbfid - TMIN_MBFID] == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ��å���� */
		return E_ID;	/* ����ID */
	}
#endif

	/* ��å������Хåե������� */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	
	mknl_unl_sys();	/* �����ƥ�Υ��å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */