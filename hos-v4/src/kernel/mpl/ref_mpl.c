/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_sys.h"



/* 可変長メモリブロックの状態参照 */
ER ref_mpl(
		ID     mplid,		/* 状態取得対象の可変長メモリプールのID番号 */
		T_RMPL *pk_rmpl)	/* 可変長メモリプール状態を返すパケットへのポインタ */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmpl == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 可変長メモリブロックの待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&mplcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rmpl->wtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rmpl->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* 空きブロックの情報(未実装) */
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
