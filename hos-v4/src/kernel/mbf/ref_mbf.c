/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_sys.h"


/* ��å������Хåե��ξ��ֻ��� */
ER ref_mbf(
		ID     mbfid,		/* ���ּ����оݤΥ�å������Хåե���ID�ֹ� */
		T_RMBF *pk_rmbf)	/* ��å������Хåե����֤��֤��ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_MKNL_TCB         *mtcb;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmbf == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ��å������Хåե��������Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rmbf->stskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rmbf->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* ��å������Хåե��μ����Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rmbf->rtskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rmbf->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* ��å������Хåե������äƤ����å��������μ���*/
	pk_rmbf->smsgcnt = mbfcb_ram->smsgcnt;
	
	/* ��å������Хåե��ΰ�ζ����ΰ�Υ������μ��� */
	pk_rmbf->fmbfsz = mbfcb_ram->fmbfsz;
	if ( pk_rmbf->fmbfsz > sizeof(UINT) )
	{
		pk_rmbf->fmbfsz -= sizeof(UINT);
	}
	else
	{
		pk_rmbf->fmbfsz = 0;
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
