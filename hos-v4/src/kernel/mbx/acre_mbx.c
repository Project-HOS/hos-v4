/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* �᡼��ܥå���������(ID�ֹ漫ư���դ�) */
ER_ID acre_mbx(
		const T_CMBX *pk_cmbx)	/* �᡼��ܥå���������������줿�ѥ��åȤؤΥݥ��� */
{
	ID mbxid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( mbxid = KERNEL_TMAX_MBXID; mbxid >= TMIN_MBXID; mbxid-- )
	{
		if ( kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( mbxid < TMIN_MBXID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* �᡼��ܥå��������� */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)mbxid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
