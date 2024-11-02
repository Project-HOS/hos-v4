/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static UB kernel_rch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
								T_KERNEL_MBFCB_RAM *mbfcb_ram);	/* １キャラクタ受信 */



/* メッセージバッファからの受信(カーネル内部関数) */
ER_UINT kernel_rcv_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		VP                       msg)			/* 受信メッセージを格納する先頭番地 */
{
	T_MKNL_TCB *mtcb;
	UINT       msgsz;
	UINT       tmpsz;
	INT        i;

	/* メッセージ存在チェック */
	if ( mbfcb_ram->smsgcnt == 0 )	/* メッセージが無い場合 */
	{
		/* 送信待ちタスクチェック */
		mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* 受信待ち行列の先頭タスクを参照 */
		if ( mtcb != NULL )
		{
			T_KERNEL_MBFDAT *mbfdat;
			
			/* 送信データ受け取り */
			mbfdat = (T_KERNEL_MBFDAT *)mtcb->data;
			__hos_bcopy(msg, mbfdat->msg, mbfdat->msgsz);	/* データコピー */

			/* 送信タスクの待ちを解除 */
			mknl_rmv_que(mtcb);				/* 待ち行列から削除 */
			mknl_rmv_tmout(mtcb);			/* タイムアウト待ち行列から削除 */
			mknl_wup_tsk(mtcb, E_OK);		/* タスクの待ち解除 */

			return (ER_UINT)mbfdat->msgsz;	/* 正常完了 */
		}

		return E_TMOUT;		/* タイムアウト */
	}
	
	/* サイズ受信 */
	msgsz = 0;
	for ( i = 0; i < sizeof(UINT); i++ )
	{
		/* 上位から順に8bitずつ読み出し */
		msgsz <<= 8;
		msgsz += kernel_rch_mbf(mbfcb_rom, mbfcb_ram);
	}
	
	/* データ受信 */
	tmpsz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->head;	/* 折り返し点までのサイズを算出 */
	if ( tmpsz >= msgsz )	/* 折り返し判定 */
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, msgsz);		/* データコピー */
	}
	else
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, tmpsz);		/* 折り返し点までコピー */
		__hos_bcopy((UB *)msg + tmpsz, (UB *)mbfcb_rom->mbf, msgsz - tmpsz);	/* 残りを先頭からコピー */
	}

	/* ポインタ更新 */
	mbfcb_ram->head += msgsz;
	if ( mbfcb_ram->head >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head -= (UINT)mbfcb_rom->mbfsz;
	}

	/* バッファ空きサイズ更新 */
	mbfcb_ram->fmbfsz += msgsz;

	/* 送信個数デクリメント */
	mbfcb_ram->smsgcnt--;

	return (ER_UINT)msgsz;	/* 送信サイズを返す */
}


/* １キャラクタ受信 */
UB kernel_rch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram)	/* メッセージバッファコントロールブロック(RAM部) */
{
	UB chr;

	/* １キャラクタ受信 */
	chr = *((UB *)mbfcb_rom->mbf + mbfcb_ram->head);

	/* ポインタ更新 */
	if ( mbfcb_ram->head + 1 < (UINT)mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head++;
	}
	else
	{
		mbfcb_ram->head = 0;
	}

	/* バッファ空きサイズ更新 */
	mbfcb_ram->fmbfsz++;
	
	return chr;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
