/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* ����Ĺ����֥�å����ֵ� */
ER rel_mpf(
		ID mpfid,		/* ����֥�å������оݤθ���Ĺ����ס����ID�ֹ� */
		VP blk)			/* �ֵѤ������֥�å�����Ƭ���� */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* ID���� */
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

	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb != NULL )
	{
		/* �Ԥ���������������Ԥ���� */
		mknl_rmv_que(mtcb);						/* ����ס�����Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mtcb->data = (VP_INT)blk;				/* �֥�å�����Ƭ���Ϥ����� */
		mknl_wup_tsk(mtcb, E_OK);				/* ���������Ԥ���� */
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	else
	{
		/* �Ԥ���������̵����Х���ס�����ֵ� */
		*(VP *)blk      = mpfcb_ram->free;
		mpfcb_ram->free = blk;
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
