/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �Ԥ����֤ζ������ */
ER rel_wai(
		ID tskid)	/* �Ԥ����֤ζ�������оݤΥ�������ID�ֹ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������ȥ���֥�å����� */
	if ( tskid == TSK_SELF )
	{
		/* ����������������Ѵ� */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* �󥿥�������ƥ����Ȥ� TSK_SELF��������� */
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_ID;		/* ����ID�ֹ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_NOEXS;		/* ���֥�������̤���� */
		}
#endif
	}

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_WAI) )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_OBJ;		/* ���֥������Ⱦ��֥��顼 */
	}
#endif

	/* �������ζ������� */
	mknl_rmv_que(&tcb_ram->mtcb);				/* �Ԥ����󤫤鳰�� */
	mknl_rmv_tmout(&tcb_ram->mtcb);				/* �����ॢ���Ȳ�� */
	mknl_wup_tsk(&tcb_ram->mtcb, E_RLWAI);		/* �����Ԥ���� */
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
