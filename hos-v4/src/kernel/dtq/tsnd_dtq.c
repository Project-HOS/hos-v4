/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �ǡ������塼�ؤ�����(�����ॢ���Ȥ���) */
ER      tsnd_dtq(
		ID     dtqid,	/* �����оݤΥǡ������塼��ID�ֹ� */
		VP_INT data,	/* �ǡ������塼����������ǡ��� */
		TMO    tmout)	/* �����ॢ���Ȼ��� */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	UINT tail;
	ER   ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
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
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	if ( mknl_ref_qhd(&dtqcb_ram->rcvque) != NULL )
	{
		/* �����Ԥ�������������г��� */
		mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* �Ԥ�������Ƭ���饿�������Ф� */
		mknl_rmv_que(mtcb);							/* �Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);						/* �����ॢ���Ȳ�� */
		mtcb->data = data;							/* �ǡ������Ǽ */
		mknl_wup_tsk(mtcb, E_OK);					/* ���������Ԥ���� */
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
		
		ercd = E_OK;
	}
	else
	{
		/* �Ԥ���������̵����Хǡ������塼�˳�Ǽ */
		dtqcb_rom = dtqcb_ram->dtqcbrom;
		if ( dtqcb_ram->datacnt >= dtqcb_rom->dtqcnt )
		{
			/* �ǡ������塼�����դʤ� */
			if ( tmout == TMO_POL )
			{
				/* �ݡ���󥰤ʤ�¨�������ॢ���� */
				ercd = E_TMOUT;
			}
			else
			{
				/* �����Ԥ������� */
				mtcb = mknl_get_run_tsk();		/* ���ߤΥ���������� */
				mtcb->data = data;				/* �ǡ�����¸ */
				mknl_wai_tsk(mtcb, TTW_SDTQ);	/* �Ԥ����֤����� */
				if ( dtqcb_rom->dtqatr & TA_TPRI )
				{
					mknl_adp_que(&dtqcb_ram->sndque, mtcb);	/* ������ͥ���ٽ���ɲ� */
				}
				else
				{
					mknl_add_que(&dtqcb_ram->sndque, mtcb);	/* FIFO����ɲ� */
				}
				
				/* ̵���Ԥ��Ǥʤ���� */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �����ॢ���ȥ��塼���ɲ� */
				}
				
				ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
				mknl_exe_tex();				/* �㳰�����μ¹� */
			}
		}
		else
		{
			/* �ǡ������塼�����˥ǡ������Ǽ */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = data;
			dtqcb_ram->datacnt++;
			
			ercd = E_OK;
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
