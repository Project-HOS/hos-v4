/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_sys.h"


/* メッセージバッファの状態参照 */
ER ref_mbf(
		ID     mbfid,		/* 状態取得対象のメッセージバッファのID番号 */
		T_RMBF *pk_rmbf)	/* メッセージバッファ状態を返すパケットへのポインタ */
{
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmbf == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* メッセージバッファの送信待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rmbf->stskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rmbf->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* メッセージバッファの受信待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rmbf->rtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rmbf->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* メッセージバッファに入っているメッセージ数の取得*/
	pk_rmbf->smsgcnt = mbfcb_ram->smsgcnt;
	
	/* メッセージバッファ領域の空き領域のサイズの取得 */
	if ( mbfcb_ram->head > mbfcb_ram->tail )
	{
		pk_rmbf->fmbfsz = mbfcb_ram->head - mbfcb_ram->tail;
	}
	else
	{
		pk_rmbf->fmbfsz = mbfcb_ram->mbfcb_rom->mbfsz - (mbfcb_ram->tail - mbfcb_ram->head);
	}
	pk_rmbf->fmbfsz -= (sizeof(UINT) + 1);

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
