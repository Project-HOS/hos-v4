/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����ϥ�ɥ��ư��� */
ER sta_cyc(
		ID cycid)	/* ư����оݤμ����ϥ�ɥ��ID�ֹ� */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	
	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < TMIN_CYCID || cycid > TMAX_CYCID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */
	
	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);
	
	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif
	
	cyccb_rom = cyccb_ram->cyccb_rom;
	
	/* �����ޥ��������� */
	cyccb_ram->lefttim = cyccb_rom->cyctim;
	
	/* �����ޥꥹ�Ȥ���Ͽ */
	kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
