/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰������ */
ER cre_flg(
		ID           flgid,		/* �����оݤΥ��٥�ȥե饰��ID�ֹ� */
		const T_CFLG *pk_cflg)	/* ���٥�ȥե饰������������줿�ѥ��åȤؤΥݥ��� */
{
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ID�����Ѳ�ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_flgcb_ram_tbl[flgid - TMIN_FLGID] == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_ID;	/* ����ID */
	}
#endif

	/* ���٥�ȥե饰������ */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
