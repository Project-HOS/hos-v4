/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



static UB kernel_rch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
								T_KERNEL_MBFCB_RAM *mbfcb_ram);	/* ������饯������ */



/* ��å������Хåե�����μ���(�����ͥ������ؿ�) */
ER_UINT kernel_rcv_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
		VP                       msg)			/* ������å��������Ǽ������Ƭ���� */
{
	UINT msgsz;
	UINT tmpsz;

	/* ��å�����¸�ߥ����å� */
	if ( mbfcb_ram->head == mbfcb_ram->tail )
	{
		return E_TMOUT;		/* �����ॢ���� */
	}
	
	/* ���������� */
	msgsz  = (UINT)kernel_rch_mbf(mbfcb_rom, mbfcb_ram) * 256;
	msgsz += (UINT)kernel_rch_mbf(mbfcb_rom, mbfcb_ram);
	
	/* �ǡ������� */
	tmpsz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->head;			/* �ޤ��֤����ޤǤΥ������򻻽� */
	if ( tmpsz >= msgsz )	/* �ޤ��֤�Ƚ�� */
	{
		memcpy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, msgsz);		/* �ǡ������ԡ� */
	}
	else
	{
		memcpy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, tmpsz);		/* �ޤ��֤����ޤǥ��ԡ� */
		memcpy((UB *)msg + tmpsz, (UB *)mbfcb_rom->mbf, msgsz - tmpsz);	/* �Ĥ����Ƭ���饳�ԡ� */
	}

	/* �ݥ��󥿹��� */
	mbfcb_ram->head += msgsz;
	if ( mbfcb_ram->head >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head -= (UINT)mbfcb_rom->mbfsz;
	}

	return E_OK;
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
	
	return chr;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
