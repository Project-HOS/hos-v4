/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰�Υ��ꥢ */
ER clr_flg(
		ID     flgid,	/* ���ꥢ�оݤΥ��٥�ȥե饰��ID�ֹ� */
		FLGPTN clrptn)	/* ���ꥢ����ӥåȥѥ�����(�ӥå����ȿž��) */
{
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	/* �ե饰�Υ��ꥢ */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn & clrptn);

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
