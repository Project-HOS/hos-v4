/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* ���ޥե��񸻤γ���(�ݡ����) */
ER pol_sem(
		ID semid)	/* �񸻳����оݤΥ��ޥե�ID�ֹ� */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	/* ���ޥե��񸻤������Ǥ���̵����Х����ॢ���� */
	if ( semcb_ram->semcnt == 0 )
	{
		ercd = E_TMOUT;		/* �����ॢ���� */
	}
	else
	{
		semcb_ram->semcnt--;	/* ���ޥե��񸻤γ��� */
		ercd = E_OK;
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
