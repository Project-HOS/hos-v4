/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスク優先順位の回転 */
void mknl_rot_rdq(
		PRI tskpri)		/* 優先順位を回転する対象の優先度 */
{
	mknl_rot_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI]);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
