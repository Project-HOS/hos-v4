/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



/* メッセージバッファからの受信(ポーリング) */
ER_UINT prcv_mbf(
		ID   mbfid,		/* 受信対象のメッセージバッファのID番号 */
		VP   msg)		/* 受信メッセージを格納する先頭番地 */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MBFDAT *mbfdat;
	ER_UINT ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > TMAX_MBFID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL )
	{
		return E_PAR;	/* パラメーター不正 */		
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

	mbfcb_rom = mbfcb_ram->mbfcb_rom;

	/* バッファ受信 */
	ercd = kernel_rcv_mbf(mbfcb_rom, mbfcb_ram, msg);
	if ( ercd != E_TMOUT )	/* タイムアウトでなければ */
	{
		/* 送信待ちタスクチェック */
		mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* 送信待ち行列先頭からタスク取り出し */
		if ( mtcb != NULL )
		{
			/* メッセージを送信 */
			mbfdat = (T_KERNEL_MBFDAT *)mtcb->data;
			if ( kernel_snd_mbf(mbfcb_rom, mbfcb_ram, mbfdat->msg, mbfdat->msgsz) == E_OK )
			{
				/* 送信タスクの待ちを解除 */
				mknl_rmv_que(mtcb);						/* 待ち行列から削除 */
				mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
				mknl_wup_tsk(mtcb, (ER_UINT)E_OK);		/* タスクの待ち解除 */
			}
		}
		ercd = E_OK;
	}
	
	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
