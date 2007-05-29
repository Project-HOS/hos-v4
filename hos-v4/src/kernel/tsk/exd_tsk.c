/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"
#include "knl_mem.h"


static void kernel_exd_tsk(VP_INT exinf);	/* ���������ν�λ�Ⱥ��(�����ƥॿ�����Ǽ¹�) */


/* ���������ν�λ�Ⱥ�� */
void exd_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* �¹��楿�����μ��� */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	/* �����ƥॿ�������������Ԥ� */
	mknl_exe_sys((FP)kernel_exd_tsk, (VP_INT)tcb_ram);
}


/* ���������ν�λ�Ⱥ��(�����ƥॿ�����Ǽ¹�) */
void kernel_exd_tsk(VP_INT exinf)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ID               tskid;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tskid   = kernel_get_tid(tcb_ram);

	/* ��������λ������ */
	mknl_ter_tsk(&tcb_ram->mtcb);
	
	/* ����β��� */
	kernel_fre_mem(tcb_ram);
	
	/* ����������ȥ���֥�å��ơ��֥뤫����Ͽ��� */
	KERNEL_TSKID_TO_TCB_RAM(tskid) = NULL;

	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_dsp();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
