/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_sys.h"



/* ����Ĺ����֥�å��ξ��ֻ��� */
ER ref_mpf(
		ID     mpfid,		/* ���ּ����оݤθ���Ĺ����ס����ID�ֹ� */
		T_RMPF *pk_rmpf)	/* ����Ĺ����ס�����֤��֤��ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	VP   blk;
	UINT blkcnt;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmpf == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* ����Ĺ����֥�å����Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rmpf->wtskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rmpf->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �����֥�å��Υ������ */
	blkcnt = 0;
	blk    = mpfcb_ram->free;
	while ( blk != NULL )
	{
		blk = *(VP *)blk;
		blkcnt++;
	}

	pk_rmpf->fblkcnt = blkcnt;
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
