/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���ޥե��񸻤γ��� */
ER wai_sem(
		ID semid)	/* �񸻳����оݤΥ��ޥե�ID�ֹ� */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;	/* ID���� */
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

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ���ޥե��񸻤������Ǥ�������� */
	if ( semcb_ram->semcnt > 0 )
	{
		semcb_ram->semcnt--;	/* ���ޥե��񸻤γ��� */
		mknl_unl_sys();			/* �����ƥ�Υ�å���� */
		return E_OK;
	}

	semcb_rom = semcb_ram->semcbrom;

	/* ���������Ԥ����֤ˤ��� */
	mtcb = mknl_get_run_tsk();
	mknl_wai_tsk(mtcb, TTW_SEM);
	if ( semcb_rom->sematr & TA_TPRI )
	{
		mknl_adp_que(&semcb_ram->que, mtcb);	/* ������ͥ���ٽ���ɲ� */
	}
	else
	{
		mknl_add_que(&semcb_ram->que, mtcb);	/* FIFO����ɲ� */
	}

	/* �������ǥ����ѥå��μ¹� */
	ercd = (ER)mknl_exe_dsp();

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
