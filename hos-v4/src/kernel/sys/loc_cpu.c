/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* CPUロック状態への移行 */
ER loc_cpu(void)
{
	mknl_loc_sys();	/* システムのロック */

	mknl_loc_cpu();	/* CPUのロック */

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
