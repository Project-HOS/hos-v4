/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���ޥե������� */
ER cre_sem(
		ID           semid,		/* �����оݤΥ��ޥե���ID�ֹ� */
		const T_CSEM *pk_csem)	/* ���ޥե�������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ��å� */

	/* ID�����Ѳ�ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_semcb_ram_tbl[semid - TMIN_SEMID] == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ��å���� */
		return E_ID;	/* ����ID */
	}
#endif

	/* ���ޥե������� */
	ercd = kernel_cre_sem(semid, pk_csem);
	
	mknl_unl_sys();	/* �����ƥ�Υ��å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */