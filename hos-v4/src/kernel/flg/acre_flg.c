/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰������(ID�ֹ漫ư���դ�) */
ER_ID acre_flg(
		const T_CFLG *pk_cflg)	/* ���٥�ȥե饰������������줿�ѥ��åȤؤΥݥ��� */
{
	ID flgid;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���Ѳ�ǽ��ID�θ��� */
	for ( flgid = KERNEL_TMAX_FLGID; flgid >= KERNEL_TMIN_FLGID; flgid-- )
	{
		if ( kernel_flgcb_ram_tbl[flgid - KERNEL_TMIN_FLGID] == NULL )
		{
			break;
		}
	}
	
	/* ID�ֹ���­�����å� */
#ifdef HOS_ERCHK_E_NOID
	if ( flgid < KERNEL_TMIN_FLGID )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOID;	/* ID�ֹ���­ */
	}
#endif

	/* ���٥�ȥե饰������ */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return (ER_ID)flgid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
