/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの起床待ち */
ER slp_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	tcb_ram = kernel_get_run_tsk();

	/* 起床要求キューイングのチェック */
	if ( tcb_ram->wupcnt > 0 )
	{
		tcb_ram->wupcnt--;
		mknl_unl_sys();		/* システムのロック解除 */
		return E_OK;
	}
	
	/* 待ち状態に設定 */
	mknl_wai_tsk(&tcb_ram->mtcb, TTW_SLP);
	
	ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
	mknl_exe_tex();				/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
