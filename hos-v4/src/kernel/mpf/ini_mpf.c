/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* ����Ĺ����ס���ν���� */
void kernel_ini_mpf(void)
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM       *mpfcb_ram;
	UB   *ptr;
	INT  i;
	UINT j;

	/* ����Ĺ����ס��륳��ȥ���֥�å��ν���� */
	for ( i = 0; i < kernel_mpfcb_cnt; i++ )
	{
		mpfcb_ram = kernel_mpfcb_ram_tbl[i];
		if ( mpfcb_ram != NULL )
		{
			mpfcb_rom = mpfcb_ram->mpfcb_rom;
			
			/* �֥�å��ν���� */
			mpfcb_ram->free = mpfcb_rom->mpf;
			ptr             = (UB *)mpfcb_rom->mpf;
			for ( j = 0; j < mpfcb_rom->blkcnt - 1; j++ )
			{
				*(VP *)ptr = (VP)(ptr + mpfcb_rom->blksz);
				ptr += mpfcb_rom->blksz;
			}
			*(VP *)ptr = NULL;	/* �ǽ��֥�å� */
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
