/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* ���ޥե��񸻤γ���(�����ॢ���Ȥ���) */
ER twai_sem(
		ID  semid,	/* �񸻳����оݤΥ��ޥե�ID�ֹ� */
		TMO tmout)	/* �����ॢ���Ȼ��� */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM       *semcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;
	}
#endif

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
	if ( tmout != TMO_POL && mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	if ( semcb_ram->semcnt > 0 )
	{
		/* ���ޥե��񸻤������Ǥ�������� */
		semcb_ram->semcnt--;	/* ���ޥե��񸻤γ��� */
		ercd = E_OK;
	}
	else
	{
		/* �����Ǥ��ʤ��ä��ʤ� */
		if ( tmout == TMO_POL )
		{
			/* �ݡ���󥰤ʤ�¨�������ॢ���� */
			ercd = E_TMOUT;
		}
		else
		{
			/* �����ॢ�����դ����Ԥ������� */
			semcb_rom = semcb_ram->semcb_rom;
			mtcb = mknl_get_run_tsk();
			mknl_wai_tsk(mtcb, TTW_SEM);
			mknl_add_que(&semcb_ram->que, mtcb, semcb_rom->sematr);	/* �Ԥ�������ɲ� */

			/* ̵���Ԥ��Ǥʤ���Х����ॢ�������� */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �����ॢ���ȥ��塼���ɲ� */
			}
			
			ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
			mknl_exe_tex();				/* �㳰�����μ¹� */
		}
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
