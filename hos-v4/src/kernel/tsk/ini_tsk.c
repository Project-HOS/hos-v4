/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����������                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"


/* �������ν���� */
void kernel_ini_tsk(void)
{
	int i;

	/* TCB��RAM���ϥ����ΰ�ˤ��Ƥ����ƥ����ɤǽ���������ۤ�����Ψ���褤 */
	for ( i = 0; i < kernel_tcb_cnt; i++ )
	{
		/* task ���ɥ쥹�Τ����Τ���¸�ߤ���ȸ��ʤ� */
		if ( kernel_tcb_ram_tbl[i] != NULL )
		{
			mknl_ini_tsk(&kernel_tcb_ram_tbl[i]->mtcb);
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
	tcb_rom = tcb_ram->tcbrom;

	mknl_unl_sys();			/* �����ƥ�Υ�å���� */

	tcb_rom->task(exinf);	/* �������¹� */

	ext_tsk();	/* �꥿������Ͻ�λ */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
