/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* 周期ハンドラの削除 */
ER del_cyc(
		ID cycid)	/* 削除対象の周期ハンドラのID番号 */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* タイマリストから外す */
	kernel_rmv_tml((T_KERNEL_TIM *)cyccb_ram);
	
	/* メモリの解放 */
	kernel_fre_mem(cyccb_ram);

	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = NULL;
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
