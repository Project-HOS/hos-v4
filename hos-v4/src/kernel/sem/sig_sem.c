/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* ���ޥե��񸻤��ֵ� */
ER sig_sem(
		ID semid)		/* ���ޥե����ֵ��оݤΥ��ޥե���ID�ֹ� */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;
	
	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */
	
	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);
	
	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	semcb_rom = semcb_ram->semcb_rom;
	
	/* ���塼���󥰥����С��ե������å� */
#ifdef HOS_ERCHK_E_QOVR
	if ( semcb_ram->semcnt >= semcb_rom->maxsem )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_QOVR;
	}
#endif
	
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb != NULL )
	{
		/* �Ԥ���������������Ԥ���� */
		mknl_rmv_que(mtcb);						/* ���ޥե����Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, E_OK);				/* ���������Ԥ���� */
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	else
	{
		semcb_ram->semcnt++;	/* ���ޥե����ֵ� */
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
