/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �᡼��ܥå�������μ���(�ݡ����) */
ER prcv_mbx(
		ID    mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		T_MSG **pk_msg)		/* �᡼��ܥå����������������å������ѥ��åȤ���Ƭ���� */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	if ( mbxcb_ram->msg != NULL )
	{
		/* �᡼��ܥå����˥ǡ���������м��Ф� */
		*pk_msg = mbxcb_ram->msg;
		mbxcb_ram->msg = mbxcb_ram->msg->next;
		ercd = E_OK;	/* ���� */
	}
	else
	{
		/* �᡼��ܥå��������ʤ饿���ॢ���� */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
