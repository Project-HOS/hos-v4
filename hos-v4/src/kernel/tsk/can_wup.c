/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク付属同期機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスク起床要求のキャンセル */
ER_UINT can_wup(
		ID tskid)	/* 起床要求のキャンセル対象のタスクID番号 */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER_UINT ercd;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return (ER_UINT)E_ID;	/* 不正ID番号 */
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
			mknl_unl_sys();			/* システムのロック解除 */
			return (ER_UINT)E_ID;	/* 不正ID番号 */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* タスクID指定時の変換 */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();				/* システムのロック解除 */
			return (ER_UINT)E_NOEXS;	/* オブジェクト未生成 */
		}
#endif
	}

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_UINT)E_OBJ;	/* オブジェクト状態エラー */
	}
#endif

	/* 起床要求のキャンセル */
	ercd = tcb_ram->wupcnt;
	tcb_ram->wupcnt = 0;

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
