/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク例外処理機能                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"


/* タスク例外処理の要求 */
ER ras_tex(
		ID     tskid,		/* 要求対象のタスクのID番号 */
		TEXPTN rasptn)		/* 要求するタスク例外処理のタスク例外要因 */
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;

	/* ID 範囲チェック */
	if ( tskid == TSK_SELF )
	{
		/* コンテキストチェック */
#ifdef HOS_ERCHK_E_ID
		if ( sns_ctx() )
		{
			return E_ID;	/* 不正ID番号 */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
		texcb = tcb_ram->texcb;
		
		mknl_loc_sys();	/* システムのロック */
	}
	else
	{
		/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
		if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
		{
			return  E_ID;	/* 不正ID番号 */
		}
#endif
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		mknl_loc_sys();	/* システムのロック */
	
		/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* システムのロック解除 */
			return E_NOEXS;		/* オブジェクト未生成 */
		}
#endif
		
		texcb = tcb_ram->texcb;
		
		/* オブジェクト状態チェック */
#ifdef HOS_ERCHK_E_OBJ
		if ( texcb == NULL || mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
		{
			mknl_unl_sys();		/* システムのロック解除 */
			return E_OBJ;		/* オブジェクト状態不正 */
		}
#endif
	}

	/* 例外処理の要求 */
	texcb->rasptn = (TEXPTN)(texcb->rasptn | rasptn);
	mknl_ras_tex(&tcb_ram->mtcb);

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
