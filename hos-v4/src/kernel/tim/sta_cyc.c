/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ϥ�ɥ�                                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



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
	
	/* ư������ */
	cyccb_ram->lefttim = cyccb_rom->cyctim;
	cyccb_ram->cycstat = TCYC_STA;
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;	
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
