/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク例外処理機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"



/* タスク例外処理の禁止 */
ER dis_tex(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( sns_ctx() )
	{
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	tcb_ram = kernel_get_run_tsk();

	mknl_loc_sys();	/* システムのロック */

	/* オブジェクト状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( tcb_ram->texcb == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_OBJ;		/* オブジェクト状態不正 */
	}
#endif

	/* 例外処理の禁止 */
	mknl_dis_tex(&tcb_ram->mtcb);

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
