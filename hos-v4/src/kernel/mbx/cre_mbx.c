/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* �᡼��ܥå��������� */
ER cre_mbx(
		ID           mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		const T_CMBX *pk_cmbx)	/* �᡼��ܥå���������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* �᡼��ܥå�������Ͽ��ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif

	/* �᡼��ܥå��������� */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
