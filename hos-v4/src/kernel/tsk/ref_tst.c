/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの状態参照(簡易版) */
ER ref_tst(
		ID     tskid,
		T_RTST *p_rtst)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > TMAX_TSKID) )
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

	/* タスク情報取得 */
	p_rtst->tskstat = mknl_get_tskstat(&tcb_ram->mtcb);
	p_rtst->tskwait = mknl_get_tskwait(&tcb_ram->mtcb);
	p_rtst->exinf   = tcb_ram->tcbrom->exinf;

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
