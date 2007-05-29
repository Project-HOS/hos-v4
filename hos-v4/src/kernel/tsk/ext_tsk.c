/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


static void kernel_ext_tsk(VP_INT exinf);	/* �������ν�λ����(�����ƥॿ�����Ǽ¹�) */



/* ���������ν�λ */
void ext_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* �¹��楿�����μ��� */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	/* �����ƥॿ�������������Ԥ� */
	mknl_exe_sys((FP)kernel_ext_tsk, (VP_INT)tcb_ram);
}



/* �������ν�λ����(�����ƥॿ�����Ǽ¹�) */
void kernel_ext_tsk(VP_INT exinf)
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tcb_rom = tcb_ram->tcb_rom;
	
	/* ��������λ������ */
	mknl_ter_tsk(&tcb_ram->mtcb);

	/* ��ư�����塼���󥰤���Ƥ����ʤ� */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_ram->actcnt--;		/* ���塼���󥰸��� */
		tcb_ram->suscnt = 0;	/* �����Ԥ��ͥ��ȥ��ꥢ */
		tcb_ram->wupcnt = 0;	/* �Ԥ�����׵ᥭ�塼���󥰥��ꥢ */

		/* ���٥����������� */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* ��Ͽ���륿���� */
				tcb_rom->exinf,			/* �������γ�ĥ���� */
				(FP)kernel_task_entry,	/* �������ε�ư���� */
				tcb_rom->itskpri,		/* �������ε�ư��ͥ���� */
				tcb_rom->stksz,			/* �������Υ����å��ΰ襵���� */
				tcb_rom->stk			/* �������Υ����å��ΰ����Ƭ���� */
			);	
	}
	
	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
