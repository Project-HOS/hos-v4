/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク制御                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 強制待ち状態からの強制再開 */
ER frsm_tsk(
		ID tskid)	/* 再開対象のタスクのID番号 */
{
		T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* オブジェクト状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS) )
	{
		/* 強制待ち状態でなければ */
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* オブジェクトの状態不正 */
	}
#endif

	/* タスクの強制待ち強制解除 */
	tcb_ram->suscnt = 0;
	mknl_rsm_tsk(&tcb_ram->mtcb);

	/* タスクディスパッチの実行 */
	mknl_exe_dsp();

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}			



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
