/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �������ν���� */
void kernel_ini_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	int i;

	/* TCB��RAM���ϥ����ΰ�ˤ��Ƥ����ƥ����ɤǽ���������ۤ�����Ψ���褤 */
	for ( i = KERNEL_TMIN_TSKID; i <= KERNEL_TMAX_TSKID; i++ )
	{
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(i);
		if ( tcb_ram != NULL )
		{
			/* �̥����ͥ���ʬ�ν���� */
			mknl_ini_tsk(&tcb_ram->mtcb);
			
			/* TA_ACT°���Τ�Τ�ư���� */
			if ( tcb_ram->tcb_rom->tskatr & TA_ACT )
			{
				act_tsk(KERNEL_TMIN_TSKID + i);
			}
		}
	}
}


/* �������Υ���ȥ꡼�ݥ���� */
void kernel_task_entry(
		VP_INT exinf)		/* �������γ�ĥ���� */
{
	register const T_KERNEL_TCB_ROM *tcb_rom;
	register T_KERNEL_TCB_RAM *tcb_ram;

	/* �������ȥ��ɥ쥹�λ��� */
	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk());
	tcb_rom = tcb_ram->tcb_rom;

	mknl_unl_sys();			/* �����ƥ�Υ�å���� */

	tcb_rom->task(exinf);	/* �������¹� */

	ext_tsk();	/* �꥿������Ͻ�λ */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
