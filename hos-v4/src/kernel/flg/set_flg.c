/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���٥�ȥե饰�Υ��å� */
ER set_flg(
		ID     flgid,		/* ���å��оݤΥ��٥�ȥե饰��ID�ֹ� */
		FLGPTN setptn)		/* ���åȤ���ӥåȥѥ����� */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
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

	/* �ե饰�Υ��å� */
	flgcb_ram->flgptn |= setptn;

	/* �Ԥ�������������е��������å� */
	if ( flgcb_ram->mtcb != NULL )
	{
		flgcb_rom = flgcb_ram->flgcbrom;
		if ( kernel_chk_flg(flgcb_ram) )
		{
			/* ���������������Ƥ���ʤ� */
			mknl_del_que(flgcb_ram->mtcb);			/* �Ԥ����󤫤鳰�� */
			mknl_del_tmout(flgcb_ram->mtcb);		/* �����ॢ���Ȳ�� */
			mknl_wup_tsk(flgcb_ram->mtcb, E_OK);	/* �Ԥ��������ε��� */

			/* �������ǥ����ѥå��μ¹� */
			mknl_exe_dsp();
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���ｪλ */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
