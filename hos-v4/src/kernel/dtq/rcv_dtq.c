/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �ǡ������塼����μ��� */
ER rcv_dtq(
		ID     dtqid,	/* �����оݤΥǡ������塼��ID�ֹ� */
		VP_INT *p_data)	/* �ǡ������塼������������ǡ��� */				
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	ER  ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
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

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	if ( mknl_ref_qhd(&dtqcb_ram->sndque) != NULL )
	{
		/* �����Ԥ�������������г��� */
		mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* �Ԥ�������Ƭ���饿�������Ф� */
		mknl_del_que(mtcb);							/* �Ԥ����󤫤��� */
		mknl_del_tmout(mtcb);						/* �����ॢ���Ȳ�� */
		*p_data = mtcb->data;						/* �ǡ�������Ф� */
		mknl_wup_tsk(mtcb, E_OK);					/* ���������Ԥ���� */

		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_dsp();
		
		ercd = E_OK;
	}
	else
	{
		/* �����Ԥ���������̵����Хǡ������塼������Ф� */
		dtqcb_rom = dtqcb_ram->dtqcbrom;
		if ( dtqcb_ram->datacnt == 0 )
		{
			/* �ǡ������塼�����ʤ�����Ԥ������� */
			mtcb = mknl_get_run_tsk();		/* ���ߤΥ���������� */
			mknl_wai_tsk(mtcb, TTW_RDTQ);	/* �Ԥ����֤����� */
			if ( dtqcb_rom->dtqatr & TA_TPRI )
			{
				mknl_adp_que(&dtqcb_ram->rcvque, mtcb);	/* ������ͥ���ٽ���ɲ� */
			}
			else
			{
				mknl_add_que(&dtqcb_ram->rcvque, mtcb);	/* FIFO����ɲ� */
			}

			/* �������ǥ����ѥå��μ¹� */
			ercd = (ER)mknl_exe_dsp();
	
			/* ���������ʤ�ǡ������Ǽ */		
			if ( ercd == E_OK )
			{
				*p_data = mtcb->data;
			}
		}
		else
		{
			/* �ǡ������塼����ǡ�������Ф� */
			*p_data = dtqcb_rom->dtq[dtqcb_ram->head];
			dtqcb_ram->head++;
			if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
			{
				dtqcb_ram->head = 0;
			}
			dtqcb_ram->datacnt--;
			
			ercd = E_OK;
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
