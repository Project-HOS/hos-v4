/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����������                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����������ٱ� */
ER dly_tsk(RELTIM dlytim)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	/* ����������ȥ���֥�å����� */
	tcb_ram = kernel_get_run_tsk();

	/* �����Ԥ����֤����� */
	mknl_wai_tsk(&tcb_ram->mtcb, TTW_DLY);
	mknl_add_tmout(&tcb_ram->mtcb, dlytim);
	
	/* �������ǥ����ѥå��μ¹� */
	ercd = (ER)mknl_exe_dsp();
	if ( ercd == E_TMOUT )
	{
		ercd = E_OK;		/* dly_tsk �ϥ����ॢ���Ȥ���Τ����� */
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
