/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_sys.h"



/* メールボックスの状態参照 */
ER ref_mbx(
		ID     mbxid,		/* 状態参照対象のメールボックスのID番号 */
		T_RMBX *pk_rmbx)	/* メールボックス状態を返すパケットへのポインタ */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	PRI        msgpri;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif

	/* パラメータのチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rmbx == NULL )
	{
		return E_PAR;	/* パラメータエラー */
	}
#endif
	
	mknl_loc_sys();	/* システムのロック */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif

	mbxcb_rom = mbxcb_ram->mbxcb_rom;

	/* メールボックスの待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&mbxcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rmbx->wtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rmbx->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* メッセージを優先度順に検索 */
	for ( msgpri = 0; msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI; msgpri++ )
	{
		if ( mbxcb_rom->mprihd[msgpri] != NULL )
		{
			break;
		}
	}

	if ( msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI )
	{
		/* メールボックスにデータがあれば取り出す */
		pk_rmbx->pk_msg = mbxcb_rom->mprihd[msgpri];
	}
	else
	{
		/* メールボックスが空なら */
		pk_rmbx->pk_msg = NULL;
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
