/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_sys.h"



/* データキューの状態参照 */
ER ref_dtq(
		ID     dtqid,		/* 状態参照対象のデータキューのID番号 */
		T_RDTQ *pk_rdtq)	/* データキュー状態を返すパケットへのポインタ */
{
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rdtq == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* データキューの送信待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rdtq->stskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
	/* タスクIDを検索 */
		pk_rdtq->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* イベントフラグの受信待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rdtq->rtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rdtq->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* データ数の取得 */
	pk_rdtq->sdtqcnt = dtqcb_ram->datacnt;

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
