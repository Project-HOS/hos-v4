/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの強制終了 */
ER ter_tsk(
		ID tskid)	/* 強制終了対象のタスクID番号 */
{						
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* IDからタスクコントロールブロックRAM部取得 */
	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* サービスコール不正使用チェック */
#ifdef HOS_ERCHK_E_ILUSE
	if ( mknl_get_run_tsk() == &tcb_ram->mtcb )		/* 実行中のタスクなら */
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_ILUSE;	/* サービスコール不正使用 */
	}
#endif

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* すでに休止状態ならば */
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* オブジェクト状態エラー */
	}
#endif

	/* 実行タスクの終了 */
	mknl_rmv_tmout(&tcb_ram->mtcb);		/* タイムアウト待ち行列につながれていれば解除 */
	mknl_ter_tsk(&tcb_ram->mtcb);		/* タスクを削除 */

	/* 起動がキューイングされていたなら */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_rom = tcb_ram->tcb_rom;

		tcb_ram->actcnt--;	/* キューイング減算 */

		/* 実行コンテキスト登録 */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				tcb_rom->exinf,			/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
		tcb_ram->suscnt = 0;	/* 強制待ちネストクリア */
		tcb_ram->wupcnt = 0;	/* 待ち解除要求キューイングクリア */
	}
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
