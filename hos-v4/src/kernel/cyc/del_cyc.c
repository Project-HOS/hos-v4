/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* �����ϥ�ɥ�κ�� */
ER del_cyc(
		ID cycid)	/* ����оݤμ����ϥ�ɥ��ID�ֹ� */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �����ޥꥹ�Ȥ��鳰�� */
	kernel_rmv_tml((T_KERNEL_TIM *)cyccb_ram);
	
	/* ����β��� */
	kernel_fre_mem(cyccb_ram);

	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = NULL;
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
