/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_sys.h"



/* �ǡ������塼�ξ��ֻ��� */
ER ref_dtq(
		ID     dtqid,		/* ���ֻ����оݤΥǡ������塼��ID�ֹ� */
		T_RDTQ *pk_rdtq)	/* �ǡ������塼���֤��֤��ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rdtq == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �ǡ������塼�������Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rdtq->stskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
	/* ������ID�򸡺� */
		pk_rdtq->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* ���٥�ȥե饰�μ����Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rdtq->rtskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rdtq->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �ǡ������μ��� */
	pk_rdtq->sdtqcnt = dtqcb_ram->datacnt;

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
