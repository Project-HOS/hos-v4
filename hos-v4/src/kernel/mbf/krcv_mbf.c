/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static UB kernel_rch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
								T_KERNEL_MBFCB_RAM *mbfcb_ram);	/* ������饯������ */



/* ��å������Хåե�����μ���(�����ͥ������ؿ�) */
ER_UINT kernel_rcv_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		VP                       msg)			/* ������å��������Ǽ������Ƭ���� */
{
	T_MKNL_TCB *mtcb;
	UINT       msgsz;
	UINT       tmpsz;
	INT        i;

	/* ��å�����¸�ߥ����å� */
	if ( mbfcb_ram->smsgcnt == 0 )	/* ��å�������̵����� */
	{
		/* �����Ԥ������������å� */
		mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* �����Ԥ��������Ƭ�������򻲾� */
		if ( mtcb != NULL )
		{
			T_KERNEL_MBFDAT *mbfdat;
			
			/* �����ǡ���������� */
			mbfdat = (T_KERNEL_MBFDAT *)mtcb->data;
			__hos_bcopy(msg, mbfdat->msg, mbfdat->msgsz);	/* �ǡ������ԡ� */

			/* �������������Ԥ����� */
			mknl_rmv_que(mtcb);				/* �Ԥ����󤫤��� */
			mknl_rmv_tmout(mtcb);			/* �����ॢ�����Ԥ����󤫤��� */
			mknl_wup_tsk(mtcb, E_OK);		/* ���������Ԥ���� */

			return (ER_UINT)mbfdat->msgsz;	/* ���ﴰλ */
		}

		return E_TMOUT;		/* �����ॢ���� */
	}
	
	/* ���������� */
	msgsz = 0;
	for ( i = 0; i < sizeof(UINT); i++ )
	{
		/* ��̤�����8bit�����ɤ߽Ф� */
		msgsz <<= 8;
		msgsz += kernel_rch_mbf(mbfcb_rom, mbfcb_ram);
	}
	
	/* �ǡ������� */
	tmpsz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->head;	/* �ޤ��֤����ޤǤΥ������򻻽� */
	if ( tmpsz >= msgsz )	/* �ޤ��֤�Ƚ�� */
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, msgsz);		/* �ǡ������ԡ� */
	}
	else
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, tmpsz);		/* �ޤ��֤����ޤǥ��ԡ� */
		__hos_bcopy((UB *)msg + tmpsz, (UB *)mbfcb_rom->mbf, msgsz - tmpsz);	/* �Ĥ����Ƭ���饳�ԡ� */
	}

	/* �ݥ��󥿹��� */
	mbfcb_ram->head += msgsz;
	if ( mbfcb_ram->head >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head -= (UINT)mbfcb_rom->mbfsz;
	}

	/* �Хåե��������������� */
	mbfcb_ram->fmbfsz += msgsz;

	/* �����Ŀ��ǥ������ */
	mbfcb_ram->smsgcnt--;

	return (ER_UINT)msgsz;	/* �������������֤� */
}


/* ������饯������ */
UB kernel_rch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram)	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
{
	UB chr;

	/* ������饯������ */
	chr = *((UB *)mbfcb_rom->mbf + mbfcb_ram->head);

	/* �ݥ��󥿹��� */
	if ( mbfcb_ram->head + 1 < (UINT)mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head++;
	}
	else
	{
		mbfcb_ram->head = 0;
	}

	/* �Хåե��������������� */
	mbfcb_ram->fmbfsz++;
	
	return chr;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
