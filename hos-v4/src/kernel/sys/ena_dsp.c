/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ディスパッチの許可 */
ER ena_dsp(void)
{
	mknl_loc_sys();	/* システムのロック */

	mknl_ena_dsp();	/* ディスパッチの許可 */
	mknl_dly_dsp();	/* 遅延ディスパッチの実行 */

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
