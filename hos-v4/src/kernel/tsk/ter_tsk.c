/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �������ζ�����λ */
ER ter_tsk(
		ID tskid)	/* ������λ�оݤΥ�����ID�ֹ� */
{						
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ID���饿��������ȥ���֥�å�RAM������ */
	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* �����ӥ��������������ѥ����å� */
#ifdef HOS_ERCHK_E_ILUSE
	if ( mknl_get_run_tsk() == &tcb_ram->mtcb )		/* �¹���Υ������ʤ� */
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_ILUSE;	/* �����ӥ��������������� */
	}
#endif

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* ���Ǥ˵ٻ߾��֤ʤ�� */
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ���֥������Ⱦ��֥��顼 */
	}
#endif

	/* �¹ԥ������ν�λ */
	mknl_rmv_tmout(&tcb_ram->mtcb);		/* �����ॢ�����Ԥ�����ˤĤʤ���Ƥ���в�� */
	mknl_ter_tsk(&tcb_ram->mtcb);		/* ���������� */

	/* ��ư�����塼���󥰤���Ƥ����ʤ� */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_rom = tcb_ram->tcb_rom;

		tcb_ram->actcnt--;	/* ���塼���󥰸��� */

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
	}
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
