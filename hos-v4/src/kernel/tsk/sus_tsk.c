/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2004 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �����Ԥ����֤ؤΰܹ� */
ER sus_tsk(
		ID tskid)	/* �ܹ��оݤΥ�����ID�ֹ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������ȥ���֥�å����� */
	if ( tskid == TSK_SELF )
	{
		/* ����������������Ѵ� */
#ifdef HOS_ERCHK_E_CTX
		if ( mknl_sns_dsp() )
		{
			/* �ǥ����ѥå��ػ߾��֤� TSK_SELF��������� */
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_CTX;		/* ����ƥ��������� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ID�ֹ��������Ѵ� */
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

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( tcb_ram == kernel_get_run_tsk() && mknl_sns_dsp() )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_CTX;		/* ����ƥ��������� */
	}
#endif

	/* ���֥������Ⱦ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_OBJ;		/* ���֥������Ⱦ������� */
	}
#endif

	/* ���֥������Ⱦ���Ƚ�� */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS )
	{
		/* ���塼���󥰥����С��ե������å� */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->suscnt >= TMAX_SUSCNT )
		{
			mknl_unl_sys();	/* �����ƥ�Υ�å���� */
			return E_QOVR;
		}
#endif
		tcb_ram->suscnt++;
	}
	else
	{
		/* �������ζ����Ԥ� */
		mknl_sus_tsk(&tcb_ram->mtcb);
	}

	/* �оݤ����������ξ�硢�ǥ����ѥå��¹� */
	if ( tcb_ram == kernel_get_run_tsk())
	{
		mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();	/* �㳰�����μ¹� */
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2004 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
