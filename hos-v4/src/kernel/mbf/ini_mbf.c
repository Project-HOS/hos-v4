/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メッセージバッファ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* メッセージバッファの初期化 */
void kernel_ini_mbf(void)
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	INT                      i;

	/* メッセージバッファコントロールブロックの初期化 */
	for ( i = KERNEL_TMIN_MBFID; i <= KERNEL_TMAX_MBFID; i++ )
	{
		mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(i);
		if ( mbfcb_ram != NULL )
		{
			mbfcb_rom = mbfcb_ram->mbfcb_rom;
			
			/* 空きサイズの初期化 */
			mbfcb_ram->fmbfsz = mbfcb_rom->mbfsz;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
