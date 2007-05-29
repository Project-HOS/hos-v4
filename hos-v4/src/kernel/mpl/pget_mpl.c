/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* ����Ĺ����֥�å��γ���(�ݡ����) */
ER pget_mpl(
		ID mplid,		/* ����֥�å������оݤβ���Ĺ����ס����ID�ֹ� */
		UINT blksz,		/* �����������֥�å��Υ�����(�Х��ȿ�) */
		VP *p_blk)		/* ������������֥�å�����Ƭ���� */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
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
		/* �����֥�å���̵����Х����ॢ���� */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
