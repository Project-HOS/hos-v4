/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ��å������Хåե�����μ���(�����ॢ���Ȥ���) */
ER_UINT trcv_mbf(
		ID   mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		VP   msg,		/* ������å��������Ǽ������Ƭ���� */
		TMO  tmout)		/* �����ॢ���Ȼ��� */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	ER_UINT                  ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( (tmout != TMO_FEVR && tmout < 0) || msg == NULL )
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

	/* �Хåե����� */
	ercd = kernel_rcv_mbf(mbfcb_rom, mbfcb_ram, msg);
	if ( ercd == E_TMOUT )	/* �����ॢ���Ȥʤ� */
	{
		if ( tmout != TMO_POL )		/* �ݡ���󥰻���Ǥʤ���� */
		{
			/* ���������Ԥ����֤ˤ��� */
			mtcb = mknl_get_run_tsk();
			mtcb->data = (VP_INT)msg;
			mknl_wai_tsk(mtcb, TTW_RMBF);
			mknl_add_que(&mbfcb_ram->rcvque, mtcb, mbfcb_rom->mbfatr);	/* �Ԥ�������ɲ� */
			
			/* ̵���Ԥ��Ǥʤ���Х����ॢ�������� */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �����ॢ���ȥ��塼���ɲ� */
			}
			
			ercd = mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
			mknl_exe_tex();				/* �㳰�����μ¹� */
		}
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
