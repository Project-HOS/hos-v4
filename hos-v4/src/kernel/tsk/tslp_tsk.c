/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �������ε����Ԥ�(�����ॢ���Ȥ���) */
ER tslp_tsk(
			TMO tmout)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

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

	/* �����׵ᥭ�塼���󥰤Υ����å� */
	if ( tcb_ram->wupcnt > 0 )
	{
		tcb_ram->wupcnt--;
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_OK;
	}

	/* �ݡ���󥰻���ʤ饿���ॢ���� */
	if ( tmout == TMO_POL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_TMOUT;
	}
	
	/* �Ԥ����֤����� */
	 mknl_wai_tsk(&tcb_ram->mtcb, TTW_SLP);
	
	/* �����ॢ�����Ԥ�������ɲ� */
	if ( tmout != TMO_FEVR )
	{
		mknl_add_tmout(&tcb_ram->mtcb, (RELTIM)tmout);
	}
	
	ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();				/* �㳰�����μ¹� */
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
