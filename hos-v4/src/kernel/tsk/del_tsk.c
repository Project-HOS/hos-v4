/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_mem.h"



/* タスクの削除 */
ER_ID del_tsk(
		ID tskid)	/* 削除対象のタスクのID番号 */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
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

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )	/* 休止状態でなければ */
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* オブジェクト状態エラー */
	}
#endif
	
	/* メモリの解放 */
	kernel_fre_mem(tcb_ram);

	/* タスクコントロールブロックテーブルから登録解除 */
	KERNEL_TSKID_TO_TCB_RAM(tskid) = NULL;


	return E_OK;		/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
