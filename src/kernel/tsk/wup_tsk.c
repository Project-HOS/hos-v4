/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの起床 */
ER wup_tsk(ID tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
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
		/* ID番号指定時の変換 */
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
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* オブジェクト状態エラー */
	}
#endif

	/* 起床要求キューイングのチェック */
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_WAI)
			|| mknl_get_tskwait(&tcb_ram->mtcb) != TTW_SLP )
	{
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->wupcnt >= TMAX_WUPCNT )
		{
			mknl_unl_sys();	/* システムのロック解除 */
			return E_QOVR;
		}
#endif
		tcb_ram->wupcnt++;
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OK;	/* 起床要求をキューイングして終了 */
	}
	
	/* タスクを起床させる */
	mknl_rmv_tmout(&tcb_ram->mtcb);			/* タイムアウト待ち行列から削除 */
	mknl_wup_tsk(&tcb_ram->mtcb, E_OK);		/* 待ち状態解除 */
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
