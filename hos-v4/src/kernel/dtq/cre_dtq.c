/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �ǡ������塼������ */
ER cre_dtq(
		ID           dtqid,		/* �����оݤΥǡ������塼��ID�ֹ� */
		const T_CDTQ *pk_cdtq)	/* �ǡ������塼������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ID�����Ѳ�ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_ID;	/* ����ID */
	}
#endif

	/* �ǡ������塼������ */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
