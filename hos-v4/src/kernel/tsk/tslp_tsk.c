/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの起床待ち(タイムアウトあり) */
ER tslp_tsk(
			TMO tmout)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

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

	/* 起床要求キューイングのチェック */
	if ( tcb_ram->wupcnt > 0 )
	{
		tcb_ram->wupcnt--;
		mknl_unl_sys();		/* システムのロック解除 */
		return E_OK;
	}

	/* ポーリング指定ならタイムアウト */
	if ( tmout == TMO_POL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_TMOUT;
	}
	
	/* 待ち状態に設定 */
	 mknl_wai_tsk(&tcb_ram->mtcb, TTW_SLP);
	
	/* タイムアウト待ち行列に追加 */
	if ( tmout != TMO_FEVR )
	{
		mknl_add_tmout(&tcb_ram->mtcb, (RELTIM)tmout);
	}
	
	ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
	mknl_exe_tex();				/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
