/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* 自タスクの遅延 */
ER dly_tsk(RELTIM dlytim)
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

	/* タスクコントロールブロック取得 */
	tcb_ram = kernel_get_run_tsk();

	/* 時間待ち状態に設定 */
	mknl_wai_tsk(&tcb_ram->mtcb, TTW_DLY);
	mknl_add_tmout(&tcb_ram->mtcb, dlytim);
	
	ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
	
	if ( ercd == E_TMOUT )
	{
		ercd = E_OK;	/* dly_tsk はタイムアウトするのが正常 */
	}
	
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
