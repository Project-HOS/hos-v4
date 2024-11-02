/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル アラームハンドラ                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* アラームハンドラの初期化 */
void kernel_ini_alm(void)
{
	T_KERNEL_ALMCB_RAM *almcb_ram;
	int i;
	
	/* 静的生成されたアラームハンドラを初期化 */
	for ( i = KERNEL_TMIN_ALMID; i <= KERNEL_TMAX_ALMID; i++ )
	{
		almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(i);
		
		if ( almcb_ram != NULL )
		{
			/* タイマハンドラ登録 */
			almcb_ram->timobj.timhdr = kernel_alm_hdr;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
