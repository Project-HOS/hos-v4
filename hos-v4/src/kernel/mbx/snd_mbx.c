/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* �᡼��ܥå����ؤ����� */
ER snd_mbx(
		ID    mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		T_MSG *pk_msg)		/* �᡼��ܥå��������������å������ѥ��åȤ���Ƭ���� */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG      *msg;
	PRI        msgpri;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	mbxcb_rom = mbxcb_ram->mbxcb_rom;

	/* ��å�����ͥ���ټ��� */
	if ( mbxcb_rom->mbxatr & TA_MPRI )	/* ͥ���ٽ�ʤ� */
	{
		msgpri = (PRI)(((T_MSG_PRI*)pk_msg)->msgpri - TMIN_MPRI);

		/* ͥ���٥����å� */
#ifdef HOS_ERCHK_E_PAR
		if ( msgpri < 0	|| msgpri > mbxcb_rom->maxmpri - TMIN_MPRI )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_PAR;
		}
#endif
	}
	else	/* ͥ���٤ʤ�(FIFO��)�ʤ� */
	{
		msgpri = 0;
	}

	mtcb = mknl_ref_qhd(&mbxcb_ram->que);		/* �Ԥ�������Ƭ����������� */
	if ( mtcb != NULL )
	{
		/* �Ԥ�������������г��� */
		mtcb->data = (VP_INT)pk_msg;			/* ��å��������Ϥ� */
		mknl_rmv_que(mtcb);						/* �᡼��ܥå������Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, E_OK);				/* ���������Ԥ���� */
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	else
	{
		/* �Ԥ����������ʤ���Х᡼��ܥå�������³ */
		if ( mbxcb_rom->mprihd[msgpri] == NULL )
		{
			/* �ǽ�Σ��Ĥ���Ͽ */
			mbxcb_rom->mprihd[msgpri] = pk_msg;
			pk_msg->next              = pk_msg;
		}
		else
		{
			/* �������ɲ� */
			msg                       = mbxcb_rom->mprihd[msgpri];
			pk_msg->next              = msg->next;
			msg->next                 = pk_msg;
			mbxcb_rom->mprihd[msgpri] = pk_msg;
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
