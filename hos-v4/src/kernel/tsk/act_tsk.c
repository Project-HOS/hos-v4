/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �������ε�ư */
ER act_tsk(
		ID tskid)	/* ������ID */
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;

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

	/* ���֥������Ⱦ���Ƚ�� */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )
	{
		/* ���˼¹Ծ��֤ʤ鵯ư�׵�򥭥塼���� */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->actcnt >= TMAX_ACTCNT )
		{
			mknl_unl_sys();	/* �����ƥ�Υ�å���� */
			return E_QOVR;	/* ���塼���󥰥����С��ե� */
		}
#endif

		/* ��ư�׵�򥭥塼���� */
		tcb_ram->actcnt++;
	}
	else
	{
		/* �ٻ߾��֤ʤ饿������ư���� */
		tcb_rom = tcb_ram->tcbrom;
	
		/* �¹ԥ���ƥ�������Ͽ */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* ��Ͽ���륿���� */
				tcb_rom->exinf,			/* �������γ�ĥ���� */
				(FP)kernel_task_entry,	/* �������ε�ư���� */
				tcb_rom->itskpri,		/* �������ε�ư��ͥ���� */
				tcb_rom->stksz,			/* �������Υ����å��ΰ襵���� */
				tcb_rom->stk			/* �������Υ����å��ΰ����Ƭ���� */
			);	
		tcb_ram->suscnt = 0;	/* �����Ԥ��ͥ��ȥ��ꥢ */
		tcb_ram->wupcnt = 0;	/* �Ԥ�����׵ᥭ�塼���󥰥��ꥢ */
		
		mknl_exe_dsp();			/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();			/* �㳰�����μ¹� */
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
