/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  μカーネル キュー操作                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タスクをキュー末尾に追加 */
void mknl_add_que(
		T_MKNL_QUE *que,	/* 追加するキュー */
		T_MKNL_TCB *mtcb,	/* 追加するタスク */
		ATR        atr)		/* 追加時の属性 */
{
	if ( atr & TA_TPRI )
	{
		mknl_adp_que(que, mtcb);	/* タスク優先度順に追加 */
	}
	else
	{
		mknl_adf_que(que, mtcb);	/* FIFO順に追加 */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
