/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



/* ��å������Хåե��ؤ�����(�����ॢ���Ȥ���) */
ER tsnd_mbf(
		ID   mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		VP   msg,		/* ������å���������Ƭ���� */
		UINT msgsz,		/* ������å������Υ�����(�Х��ȿ�) */
		TMO  tmout)		/* �����ॢ���Ȼ��� */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MBFDAT mbfdat;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > TMAX_MBFID )
	{
		return E_ID;	/* ID���� */
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
		if ( ercd == E_TMOUT )	/* �����ॢ���Ȥʤ� */
		{
			if ( tmout != TMO_POL )		/* �ݡ���󥰻���Ǥʤ���� */
			{
				/* ���������Ԥ����֤ˤ��� */
				mtcb = mknl_get_run_tsk();
				mbfdat.msg   = msg;
				mbfdat.msgsz = msgsz;
				mtcb->data   = &mbfdat;
				mknl_wai_tsk(mtcb, TTW_SMBF);
				mknl_add_que(&mbfcb_ram->sndque, mtcb, mbfcb_rom->mbfatr);	/* �Ԥ�������ɲ� */
	
				/* ̵���Ԥ��Ǥʤ���Х����ॢ�������� */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �����ॢ���ȥ��塼���ɲ� */
				}

				ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
				mknl_exe_tex();				/* �㳰�����μ¹� */
			}
		}
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
