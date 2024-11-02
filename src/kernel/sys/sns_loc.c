/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* CPUロック状態の参照 */
BOOL sns_loc(void)
{
	BOOL state;
	
	mknl_loc_sys();	/* システムのロック */

	state = mknl_sns_loc();		/* CPUロック状態の参照 */

	mknl_unl_sys();	/* システムのロック解除 */

	return state;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
