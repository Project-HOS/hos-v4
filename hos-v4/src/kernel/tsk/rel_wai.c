/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* 待ち状態の強制解除 */
ER rel_wai(
		ID tskid)	/* 待ち状態の強制解除対象のタスクのID番号 */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* タスクコントロールブロック取得 */
	if ( tskid == TSK_SELF )
	{
		/* 自タスク指定時の変換 */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* 非タスクコンテキストで TSK_SELF指定は不正 */
			mknl_unl_sys();		/* システムのロック解除 */
			return E_ID;		/* 不正ID番号 */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* システムのロック解除 */
			return E_NOEXS;		/* オブジェクト未生成 */
		}
#endif
	}

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_WAI) )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_OBJ;		/* オブジェクト状態エラー */
	}
#endif

	/* タスクの強制起床 */
	mknl_rmv_que(&tcb_ram->mtcb);				/* 待ち行列から外す */
	mknl_rmv_tmout(&tcb_ram->mtcb);				/* タイムアウト解除 */
	mknl_wup_tsk(&tcb_ram->mtcb, E_RLWAI);		/* 強制待ち解除 */
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
