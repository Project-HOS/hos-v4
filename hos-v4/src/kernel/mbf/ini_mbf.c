/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��å������Хåե�                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ��å������Хåե��ν���� */
void kernel_ini_mbf(void)
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	INT                      i;

	/* ��å������Хåե�����ȥ���֥�å��ν���� */
	for ( i = KERNEL_TMIN_MBFID; i <= KERNEL_TMAX_MBFID; i++ )
	{
		mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(i);
		if ( mbfcb_ram != NULL )
		{
			mbfcb_rom = mbfcb_ram->mbfcb_rom;
			
			/* �����������ν���� */
			mbfcb_ram->fmbfsz = mbfcb_rom->mbfsz;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
