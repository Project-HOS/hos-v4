/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"
#include "knl_mem.h"



/* ���������ν�λ�Ⱥ�� */
void exd_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb_run;
	ID tskid;

	/* �¹��楿�����μ��� */
	mtcb_run = mknl_get_run_tsk();

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* �¹ԥ������ν�λ */
	mknl_ext_tsk(mtcb_run);

	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);
	tskid = kernel_get_tid(tcb_ram);
	
	/* ����β���(�����ƥ��å�����ޤǤϲ��������ΰ������Ǥ��뤳�Ȥ��ݾ㤹��) */
	kernel_fre_mem(tcb_ram);

	/* ����������ȥ���֥�å��ơ��֥뤫����Ͽ��� */
	kernel_tcb_ram_tbl[tskid - TMIN_TSKID] = NULL;

	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
