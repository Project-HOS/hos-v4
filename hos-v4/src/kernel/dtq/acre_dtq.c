/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �ǡ������塼������(ID�ֹ漫ư���դ�) */
ER_ID acre_dtq(
		const T_CDTQ *pk_cdtq)	/* �ǡ������塼������������줿�ѥ��åȤؤΥݥ��� */
{
	ID dtqid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( dtqid = TMAX_DTQID; dtqid >= TMIN_DTQID; dtqid-- )
	{
		if ( kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( dtqid < TMIN_DTQID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* �ǡ������塼������ */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)dtqid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
