/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスク優先度の変更 */
ER chg_pri(
		ID tskid,		/* 変更対象のタスクID番号 */
		PRI tskpri)		/* 変更後のベース優先度 */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	/* パラメーター範囲チェック */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI || tskpri > TMAX_TPRI )
	{
		return E_PAR;	/* パラメーター不正 */
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

	/* 起動時優先度指定の場合 */
	if ( tskpri == TPRI_INI )
	{
		tskpri = tcb_ram->tcb_rom->itskpri;
	}

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* 休止状態ならば */
	{
		return E_OBJ;	/* オブジェクト状態エラー */
	}
#endif

	/* 優先度変更 */
	mknl_chg_pri(&tcb_ram->mtcb, tskpri);
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
