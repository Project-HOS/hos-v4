/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



static void kernel_sch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
						T_KERNEL_MBFCB_RAM *mbfcb_ram, UB chr);	/* ������饯������ */



/* ��å������Хåե��ؤ����� */
ER kernel_snd_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		VP                       msg,			/* ������å���������Ƭ���� */
		UINT                     msgsz)			/* ������å������Υ�����(�Х��ȿ�) */
{
	UINT fresz;

	/* �������������� */
	if ( mbfcb_ram->head > mbfcb_ram->tail )
	{
		fresz = mbfcb_ram->head - mbfcb_ram->tail - 1;
	}
	else
	{
		fresz = (UINT)mbfcb_rom->mbfsz - (mbfcb_ram->tail - mbfcb_ram->head) - 1;
	}
	
	/* ������ǽȽ�� */
	if ( fresz < msgsz + 2 )
	{
		return E_TMOUT;		/* �����ॢ���� */
	}
	
	/* ���������� */
	kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)(msgsz / 256));
	kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)(msgsz % 256));

	/* �ǡ������� */
	fresz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->tail;	/* �Хåե��ޤ��֤��ޤǤζ������������� */
	if ( fresz >= msgsz )								/* �ޤ��֤����פ�Ƚ�� */
	{
		memcpy((UB *)mbfcb_rom->mbf + mbfcb_ram->tail, msg, msgsz);		/* �ǡ������ԡ� */
	}
	else
	{
		memcpy((UB *)mbfcb_rom->mbf + mbfcb_ram->tail, msg, fresz);		/* �ޤ��֤����ޤǥ��ԡ� */
		memcpy((UB *)mbfcb_rom->mbf, (UB *)msg + fresz, msgsz - fresz);	/* �Ĥ����Ƭ���饳�ԡ� */
	}

	/* �ݥ��󥿹��� */
	mbfcb_ram->tail += msgsz;
	if ( mbfcb_ram->tail >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->tail -= (UINT)mbfcb_rom->mbfsz;
	}

	return E_OK;
}


/* ������饯������ */
void kernel_sch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		UB                       chr)			/* �������륭��饯�� */
{
	/* ������饯������ */
	*((UB *)mbfcb_rom->mbf + mbfcb_ram->tail) = chr;

	/* �ݥ��󥿹��� */
	if ( mbfcb_ram->tail + 1 < (UINT)mbfcb_rom->mbfsz )
	{
		mbfcb_ram->tail++;
	}
	else
	{
		mbfcb_ram->tail = 0;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
