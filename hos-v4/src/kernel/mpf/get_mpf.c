/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* ����Ĺ����֥�å��γ��� */
ER get_mpf(
		ID mpfid,		/* ����֥�å������оݤθ���Ĺ����ס����ID�ֹ� */
		VP *p_blk)		/* ������������֥�å�����Ƭ���� */
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM       *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	if ( mpfcb_ram->free != NULL )
	{
		/* �����֥�å�������г�����Ƥ� */
		*p_blk          = mpfcb_ram->free;
		mpfcb_ram->free = *(VP *)mpfcb_ram->free;	/* ���ζ������ꥢ������ */
		ercd = E_OK;
	}
	else
	{
		/* �����֥�å���̵������Ԥ������� */
		mpfcb_rom = mpfcb_ram->mpfcb_rom;
		mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(mtcb, TTW_MPF);
		mknl_add_que(&mpfcb_ram->que, mtcb, mpfcb_rom->mpfatr);	/* �Ԥ�������ɲ� */
		
		ercd = (ER)mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		
		if ( ercd == E_OK )
		{
			*p_blk = (VP)mtcb->data;	/* �����֥�å���Ƭ���ϳ�Ǽ */
		}
		
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
