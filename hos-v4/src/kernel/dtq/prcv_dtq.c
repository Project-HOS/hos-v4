/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �ǡ������塼����μ���(�ݡ����) */
ER prcv_dtq(
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

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	dtqcb_rom = dtqcb_ram->dtqcbrom;

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
			/* �ǡ������塼�����������Ԥ���������̵����Х����ॢ���� */
			ercd = E_TMOUT;
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
