/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* ���ޥե�������(ID�ֹ漫ư���դ�) */
ER_ID acre_sem(
		const T_CSEM *pk_csem)	/* ���ޥե�������������줿�ѥ��åȤؤΥݥ��� */
{
	ID semid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( semid = TMAX_SEMID; semid >= TMIN_SEMID; semid-- )
	{
		if ( kernel_semcb_ram_tbl[semid - TMIN_SEMID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( semid < TMIN_SEMID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* ���ޥե������� */
	ercd = kernel_cre_sem(semid, pk_csem);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)semid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
