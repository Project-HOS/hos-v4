/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����������                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���������ν�λ */
void ext_tsk()
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb;

	mtcb = mknl_get_run_tsk();

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* �¹ԥ������ν�λ */
	mknl_ext_tsk(mtcb);

	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk());
	tcb_rom = tcb_ram->tcbrom;

	/* ��ư�����塼���󥰤���Ƥ����ʤ� */
	if ( tcb_ram->actcnt > 0 )
	{
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

	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
