/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �������ε��� */
ER wup_tsk(ID tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > TMAX_TSKID) )
	{
		return E_ID;	/* ����ID�ֹ� */
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
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_ID;		/* ����ID�ֹ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ID�ֹ��������Ѵ� */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_NOEXS;		/* ���֥�������̤���� */
		}
#endif
	}

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ���֥������Ⱦ��֥��顼 */
	}
#endif

	/* �����׵ᥭ�塼���󥰤Υ����å� */
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_WAI)
			|| mknl_get_tskwait(&tcb_ram->mtcb) != TTW_SLP )
	{
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->wupcnt >= TMAX_WUPCNT )
		{
			mknl_unl_sys();	/* �����ƥ�Υ�å���� */
			return E_QOVR;
		}
#endif
		tcb_ram->wupcnt++;
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OK;	/* ���֥�������̤���� */
	}
	
	/* �������򵯾������� */
	mknl_del_tmout(&tcb_ram->mtcb);			/* �����ॢ�����Ԥ����󤫤��� */
	mknl_wup_tsk(&tcb_ram->mtcb, E_OK);		/* �Ԥ����ֲ�� */
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
