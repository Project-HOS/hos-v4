/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* ����Ĺ����֥�å��γ��� */
ER get_mpl(
		ID   mplid,		/* ����֥�å������оݤβ���Ĺ����ס����ID�ֹ� */
		UINT blksz,		/* �����������֥�å��Υ�����(�Х��ȿ�) */
		VP   *p_blk)	/* ������������֥�å�����Ƭ���� */
{
	const T_KERNEL_MPLCB_ROM *mplcb_rom;
	T_KERNEL_MPLCB_RAM       *mplcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MPLINF          mplinf;
	VP mem;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
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

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ������ݤ˥ȥ饤 */
	mem = kernel_alc_hep(&mplcb_ram->hep, blksz);

	if ( mem != NULL )
	{
		/* ����������� */
		*p_blk          = mem;
		ercd = E_OK;
	}
	else
	{
		/* ������̵������Ԥ������� */
		mplcb_rom = mplcb_ram->mplcb_rom;
		mtcb = mknl_get_run_tsk();
		mplinf.blksz = blksz;
		mplinf.p_blk = p_blk;
		mtcb->data = (VP_INT)&mplinf;
		mknl_wai_tsk(mtcb, TTW_MPL);
		mknl_add_que(&mplcb_ram->que, mtcb, mplcb_rom->mplatr);	/* �Ԥ�������ɲ� */
		
		ercd = (ER)mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
				
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
