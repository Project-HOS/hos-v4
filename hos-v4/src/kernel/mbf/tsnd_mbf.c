/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



/* メッセージバッファへの送信(タイムアウトあり) */
ER tsnd_mbf(
		ID   mbfid,		/* 送信対象のメッセージバッファのID番号 */
		VP   msg,		/* 送信メッセージの先頭番地 */
		UINT msgsz,		/* 送信メッセージのサイズ(バイト数) */
		TMO  tmout)		/* タイムアウト指定 */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MBFDAT mbfdat;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > TMAX_MBFID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( tmout != TMO_POL && mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

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

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL || msgsz > mbfcb_rom->maxmsz )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_PAR;	/* パラメーター不正 */		
	}
#endif

	/* 受信待ちタスクチェック */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* 受信待ち行列先頭からタスク取り出し */
	if ( mtcb != NULL )
	{
		/* 受信タスクの待ちを解除 */
		memcpy((VP)mtcb->data, msg, msgsz);		/* データコピー */
		mknl_rmv_que(mtcb);						/* 待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, (ER_UINT)msgsz);		/* タスクの待ち解除 */
		ercd = E_OK;
	}
	else
	{
		/* 送信 */
		ercd = kernel_snd_mbf(mbfcb_rom, mbfcb_ram, msg, msgsz);
		if ( ercd == E_TMOUT )	/* タイムアウトなら */
		{
			if ( tmout != TMO_POL )		/* ポーリング指定でなければ */
			{
				/* タスクを待ち状態にする */
				mtcb = mknl_get_run_tsk();
				mbfdat.msg   = msg;
				mbfdat.msgsz = msgsz;
				mtcb->data   = &mbfdat;
				mknl_wai_tsk(mtcb, TTW_SMBF);
				mknl_add_que(&mbfcb_ram->sndque, mtcb, mbfcb_rom->mbfatr);	/* 待ち行列に追加 */
	
				/* 無限待ちでなければタイムアウト設定 */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* タイムアウトキューに追加 */
				}

				ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
				mknl_exe_tex();				/* 例外処理の実行 */
			}
		}
	}
	
	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
