/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



/* ��å������Хåե��ؤ�����(�ݡ����) */
ER psnd_mbf(
		ID   mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		VP   msg,		/* ������å���������Ƭ���� */
		UINT msgsz)		/* ������å������Υ�����(�Х��ȿ�) */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	mbfcb_rom = mbfcb_ram->mbfcb_rom;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL || msgsz > mbfcb_rom->maxmsz )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_PAR;	/* �ѥ�᡼�������� */		
	}
#endif

	/* �����Ԥ������������å� */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* �����Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb != NULL )
	{
		/* �������������Ԥ����� */
		memcpy((VP)mtcb->data, msg, msgsz);		/* �ǡ������ԡ� */
		mknl_rmv_que(mtcb);						/* �Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, (ER_UINT)msgsz);		/* ���������Ԥ���� */
		ercd = E_OK;
	}
	else
	{
		/* ���� */
		ercd = kernel_snd_mbf(mbfcb_rom, mbfcb_ram, msg, msgsz);
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
