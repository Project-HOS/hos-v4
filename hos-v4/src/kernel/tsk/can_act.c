/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスク起動要求のキャンセル */
ER_UINT can_act(
		ID tskid)		/* タスクID */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER_UINT ercd;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > TMAX_TSKID) )
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
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);
	}

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* 起動要求のキャンセル */
	ercd = (ER)tcb_ram->actcnt;
	tcb_ram->actcnt = 0;

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;	/* 現在のキューイング値を返す */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
