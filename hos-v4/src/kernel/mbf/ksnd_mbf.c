/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static void kernel_sch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
						T_KERNEL_MBFCB_RAM *mbfcb_ram, UB chr);	/* ������饯������ */



/* ��å������Хåե��ؤ����� */
ER kernel_snd_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		VP                       msg,			/* ������å���������Ƭ���� */
		UINT                     msgsz)			/* ������å������Υ�����(�Х��ȿ�) */
{
	T_MKNL_TCB *mtcb;
	SIZE       fresz;
	SIZE       tail;
	INT        i;

	/* �����Ԥ�������������å� */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* �����Ԥ��������Ƭ�������򻲾� */
	if ( mtcb != NULL )
	{
		return E_TMOUT;		/* �����Ԥ������ˤ���Х����ॢ���� */
	}

	/* �����Ԥ������������å� */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* �����Ԥ��������Ƭ�������򻲾� */
	if ( mtcb != NULL )
	{
		/* �������������Ԥ����� */
		__hos_bcopy((VP)mtcb->data, msg, msgsz);		/* �ǡ������ԡ� */
		mknl_rmv_que(mtcb);						/* �Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, (ER_UINT)msgsz);		/* ���������Ԥ���� */

		return E_OK;	/* ���ﴰλ */
	}

	/* ���������������å� */
	if ( mbfcb_ram->fmbfsz < msgsz + sizeof(UINT) )
	{
		return E_TMOUT;		/* �����ॢ���� */
	}
	
	/* ���������� */
	for ( i = sizeof(UINT) - 1; i >= 0; i-- )
	{
		/* ��̤�����8bitñ�̤ǽ񤭹��� */
		kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)((msgsz >> (i * 8)) & 0xff));
	}

	/* �������ֻ��� */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* �ǡ������� */
	fresz = (UINT)mbfcb_rom->mbfsz - tail;	/* �Хåե��ޤ��֤��ޤǤζ������������� */
	if ( fresz >= msgsz )					/* �ޤ��֤����פ�Ƚ�� */
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, msgsz);				/* �ǡ������ԡ� */
	}
	else
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, fresz);				/* �ޤ��֤����ޤǥ��ԡ� */
		__hos_bcopy((UB *)mbfcb_rom->mbf, (UB *)msg + fresz, msgsz - fresz);	/* �Ĥ����Ƭ���饳�ԡ� */
	}

	/* �������������� */
	mbfcb_ram->fmbfsz -= msgsz;

	/* �����Ŀ����󥯥���� */
	mbfcb_ram->smsgcnt++;

	return E_OK;
}


/* ������饯������ */
void kernel_sch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		UB                       chr)			/* �������륭��饯�� */
{
	SIZE tail;

	/* �������ֻ��� */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* ������饯������ */
	*((UB *)mbfcb_rom->mbf + tail) = chr;

	/* �Хåե��������������� */
	mbfcb_ram->fmbfsz--;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
