/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �����������׵�Υ���󥻥� */
ER_UINT can_wup(
		ID tskid)	/* �����׵�Υ���󥻥��оݤΥ�����ID�ֹ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER_UINT ercd;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return (ER_UINT)E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������ȥ���֥�å����� */
	if ( tskid == TSK_SELF )
	{
		/* ����������������Ѵ� */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* �󥿥�������ƥ����Ȥ� TSK_SELF��������� */
			mknl_unl_sys();			/* �����ƥ�Υ�å���� */
			return (ER_UINT)E_ID;	/* ����ID�ֹ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ������ID��������Ѵ� */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();				/* �����ƥ�Υ�å���� */
			return (ER_UINT)E_NOEXS;	/* ���֥�������̤���� */
		}
#endif
	}

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return (ER_UINT)E_OBJ;	/* ���֥������Ⱦ��֥��顼 */
	}
#endif

	/* �����׵�Υ���󥻥� */
	ercd = tcb_ram->wupcnt;
	tcb_ram->wupcnt = 0;

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
