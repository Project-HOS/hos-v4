/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_mem.h"



/* �������κ�� */
ER_ID del_tsk(
		ID tskid)	/* ����оݤΥ�������ID�ֹ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ��å� */

	/* ID���饿��������ȥ�����֥��å�RAM������ */
	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ��å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )	/* �ٻ߾��֤Ǥʤ���� */
	{
		mknl_unl_sys();	/* �����ƥ�Υ��å���� */
		return E_OBJ;	/* ���֥������Ⱦ��֥��顼 */
	}
#endif
	
	/* ����β��� */
	kernel_fre_mem(tcb_ram);

	/* ����������ȥ�����֥��å��ơ��֥뤫����Ͽ��� */
	kernel_tcb_ram_tbl[tskid - TMIN_TSKID] = NULL;


	return E_OK;		/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */