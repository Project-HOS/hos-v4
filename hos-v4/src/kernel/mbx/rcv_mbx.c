/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* �᡼��ܥå�������μ��� */
ER rcv_mbx(			
		ID    mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		T_MSG **pk_msg)		/* �᡼��ܥå����������������å������ѥ��åȤ���Ƭ���� */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG *msg;
	PRI   msgpri;
	ER    ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
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
	
	/* ��å�������ͥ���ٽ�˸��� */
	for ( msgpri = 0; msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI; msgpri++ )
	{
		if ( mbxcb_rom->mprihd[msgpri] != NULL )
		{
			break;
		}
	}

	if ( msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI )
	{
		/* �᡼��ܥå����˥ǡ���������м��Ф� */
		msg = mbxcb_rom->mprihd[msgpri];
		if ( msg == msg->next )		/* �Ǹ�Σ��Ĥʤ� */
		{
			*pk_msg                   = msg;
			mbxcb_rom->mprihd[msgpri] = NULL;
		}
		else
		{
			*pk_msg   = msg->next;
			msg->next = msg->next->next;
		}
		ercd = E_OK;	/* ���� */
	}
	else
	{
		/* �᡼��ܥå��������ʤ��Ԥ������� */
		mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(mtcb, TTW_MBX);
		mknl_add_que(&mbxcb_ram->que, mtcb, mbxcb_ram->mbxcb_rom->mbxatr);	/* �Ԥ�������ɲ� */
		
		ercd = (ER)mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		
		/* ��������������ǡ������Ǽ */
		if ( ercd == E_OK )
		{
			*pk_msg = (T_MSG *)mtcb->data;
		}
		
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
