/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �������㳰������ǽ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �������㳰��������ȥ꡼�ݥ����(�̥����ͥ���ƤӽФ�) */
void kernel_tex_entry(void)
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;
	TEXPTN rasptn;
	
	tcb_ram = kernel_get_run_tsk();
	texcb   = tcb_ram->texcb;
	
	/* �������㳰�װ����ꥢ */
	rasptn = texcb->rasptn;
	texcb->rasptn = 0;
	
	mknl_dis_tex(&tcb_ram->mtcb);	/* �������㳰�����ζػ� */
	mknl_unl_sys();					/* �����ƥ�Υ�å���� */

	texcb->texrtn(rasptn);			/* �������㳰�����롼����θƤӽФ� */

	mknl_loc_sys();					/* �����ƥ�Υ�å� */
	mknl_ena_tex(&tcb_ram->mtcb);	/* �������㳰�����ε��� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
