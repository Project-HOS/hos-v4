/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���顼��ϥ�ɥ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* ���顼��ϥ�ɥ��ư��� */
ER sta_alm(
		ID     almid,	/* ư����оݤΥ��顼��ϥ�ɥ��ID�ֹ� */
		RELTIM almtim)	/* ���顼��ϥ�ɥ�ε�ư����(���л���) */
{
	const T_KERNEL_ALMCB_ROM *almcb_rom;
	T_KERNEL_ALMCB_RAM *almcb_ram;
	
	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( almid < TMIN_ALMID || almid > TMAX_ALMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */
	
	almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(almid);
	
	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( almcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif
	
	almcb_rom = almcb_ram->almcb_rom;
	
	/* �����ޥ��������� */
	almcb_ram->lefttim = almtim;
	
	/* �����ޥꥹ�Ȥ���Ͽ */
	kernel_add_tml((T_KERNEL_TIM *)almcb_ram);
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
