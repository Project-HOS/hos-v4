/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �ǡ������塼�ؤ�����(�ݡ����) */
ER psnd_dtq(
		ID     dtqid,	/* �����оݤΥǡ������塼��ID�ֹ� */
		VP_INT data)	/* �ǡ������塼����������ǡ��� */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	UINT tail;
	ER   ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
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
		dtqcb_rom = dtqcb_ram->dtqcb_rom;
		if ( dtqcb_ram->datacnt >= dtqcb_rom->dtqcnt )
		{
			/* �ǡ������塼�����դʤ饿���ॢ���� */
			ercd = E_TMOUT;
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
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
