/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �ǡ������塼����μ��� */
ER trcv_dtq(
		ID     dtqid,	/* �����оݤΥǡ������塼��ID�ֹ� */
		VP_INT *p_data,	/* �ǡ������塼������������ǡ��� */				
		TMO    tmout)	/* �����ॢ���Ȼ��� */
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

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR 
	if ( (tmout != TMO_FEVR && tmout < 0) || p_data == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( tmout != TMO_POL &&  mknl_sns_wai() )
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

	dtqcb_rom = dtqcb_ram->dtqcb_rom;

	if ( dtqcb_ram->datacnt == 0 )
	{
		/* �ǡ������塼�����ʤ� */
		if ( mknl_ref_qhd(&dtqcb_ram->sndque) != NULL )
		{
			/* �����Ԥ�������������г��� */
			mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* �Ԥ�������Ƭ���饿�������Ф� */
			mknl_rmv_que(mtcb);							/* �Ԥ����󤫤��� */
			mknl_rmv_tmout(mtcb);						/* �����ॢ���Ȳ�� */
			*p_data = mtcb->data;						/* �ǡ�������Ф� */
			mknl_wup_tsk(mtcb, E_OK);					/* ���������Ԥ���� */
			
			mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
			mknl_exe_tex();		/* �㳰�����μ¹� */
			
			ercd = E_OK;
		}
		else
		{
			/* �����Ԥ���������̵������Ԥ������� */
			if ( tmout == TMO_POL )
			{
				/* �ݡ���󥰤ʤ�¨�������ॢ���� */
				ercd = E_TMOUT;
			}
			else
			{
				/* �����Ԥ������� */
				mtcb = mknl_get_run_tsk();		/* ���ߤΥ���������� */
				mknl_wai_tsk(mtcb, TTW_RDTQ);	/* �Ԥ����֤����� */
				mknl_add_que(&dtqcb_ram->rcvque, mtcb, dtqcb_rom->dtqatr);	/* �Ԥ�������ɲ� */
				
				/* ̵���Ԥ��Ǥʤ���� */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �����ॢ���ȥ��塼���ɲ� */
				}
				
				ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
				
				/* ���������ʤ�ǡ������Ǽ */		
				if ( ercd == E_OK )
				{
					*p_data = mtcb->data;
				}
				
				mknl_exe_tex();		/* �㳰�����μ¹� */
			}
		}
	}
	else
	{
		/* �ǡ������塼����ǡ�������Ф� */
		*p_data = dtqcb_rom->dtq[dtqcb_ram->head];
		dtqcb_ram->head++;
		if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
		{
			dtqcb_ram->head -= dtqcb_rom->dtqcnt;
		}
		
		/* �����Ԥ�������������ʤ鳫�� */
		mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);
		if ( mtcb!= NULL )
		{
			UINT tail;
			
			/* �ǡ������塼�����˥ǡ������Ǽ */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt - 1;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = mtcb->data;
			
			mknl_rmv_que(mtcb);			/* �Ԥ����󤫤��� */
			mknl_rmv_tmout(mtcb);		/* �����ॢ���Ȳ�� */
			mknl_wup_tsk(mtcb, E_OK);	/* ���������Ԥ���� */
			
			mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
			mknl_exe_tex();		/* �㳰�����μ¹� */
		}
		else
		{
			dtqcb_ram->datacnt--;
		}
		
		ercd = E_OK;
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
