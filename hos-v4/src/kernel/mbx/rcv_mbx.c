/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �᡼��ܥå�������μ��� */
ER rcv_mbx(			
		ID    mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		T_MSG **pk_msg)		/* �᡼��ܥå����������������å������ѥ��åȤ���Ƭ���� */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
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

	if ( mbxcb_ram->msg != NULL )
	{
		/* �᡼��ܥå����˥ǡ���������м��Ф� */
		*pk_msg = mbxcb_ram->msg;
		mbxcb_ram->msg = mbxcb_ram->msg->next;
		ercd = E_OK;	/* ���� */
	}
	else
	{
		/* �᡼��ܥå��������ʤ��Ԥ������� */
		mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(mtcb, TTW_MBX);
		if ( mbxcb_ram->mbxcbrom->mbxatr & TA_TPRI )
		{
			mknl_adp_que(&mbxcb_ram->que, mtcb);	/* ������ͥ���ٽ���ɲ� */
		}
		else
		{
			mknl_add_que(&mbxcb_ram->que, mtcb);	/* FIFO����ɲ� */
		}
		
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
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
