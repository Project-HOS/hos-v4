/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_mem.h"



/* ����Ĺ����ס���κ�� */
ER del_mpl(
		ID mplid)	/* ����оݤβ���Ĺ����ס����ID�ֹ� */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �Ԥ��������β�� */
	mknl_clr_que(&mplcb_ram->que);
	
	/* ����β��� */
	kernel_fre_mem(mplcb_ram);
	KERNEL_MPLID_TO_MPLCB_RAM(mplid) = NULL;
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
