/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"



/* ����Ĺ����ס���κ�� */
ER del_mpf(
		ID mpfid)	/* ����оݤθ���Ĺ����ס����ID�ֹ� */
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mpfcb_ram = kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID];
	mpfcb_rom = mpfcb_ram->mpfcb_rom;

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �Ԥ��������β�� */
	mknl_clr_que(&mpfcb_ram->que);
	
	/* ����β��� */
	kernel_fre_mem(mpfcb_rom->mpf);	
	kernel_fre_mem(mpfcb_ram);
	kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID] = NULL;
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
