/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



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
	
	ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
	
	if ( ercd == E_TMOUT )
	{
		ercd = E_OK;	/* dly_tsk �ϥ����ॢ���Ȥ���Τ����� */
	}
	
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
