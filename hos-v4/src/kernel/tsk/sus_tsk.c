/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* 強制待ち状態への移行 */
ER sus_tsk(
		ID tskid)	/* 移行対象のタスクID番号 */
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

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( tcb_ram == kernel_get_run_tsk() )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_CTX;		/* コンテキスト不正 */
	}
#endif

	/* オブジェクト状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_OBJ;		/* オブジェクト状態不正 */
	}
#endif

	/* オブジェクト状態判定 */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS )
	{
		/* キューイングオーバーフローチェック */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->suscnt >= TMAX_SUSCNT )
		{
			mknl_unl_sys();	/* システムのロック解除 */
			return E_QOVR;
		}
#endif
		tcb_ram->suscnt++;
	}
	else
	{
		/* タスクの強制待ち */
		mknl_sus_tsk(&tcb_ram->mtcb);
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
