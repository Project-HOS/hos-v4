/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
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
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���٥�ȥե饰����Ͽ��ǽ���ɤ��������å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_FLGID_TO_FLGCB_RAM(flgid) != NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ������Ͽ�Ѥ� */
	}
#endif

	/* ���٥�ȥե饰������ */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
