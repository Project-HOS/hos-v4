/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_sys.h"



/* ���ޥե��ξ��ֻ��� */
ER ref_sem(
		ID     semid,		/* ���ֻ����оݤΥ��ޥե���ID�ֹ� */
		T_RSEM *pk_rsem)	/* ���ޥե����֤��֤��ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif

	/* �ѥ�᡼���Υ����å� */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rsem == NULL )
	{
		return E_PAR;	/* �ѥ�᡼�����顼 */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ���ޥե����Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rsem->wtskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rsem->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* ���ޥե��θ��ߤλ񸻿����� */
	pk_rsem->semcnt = semcb_ram->semcnt;

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
