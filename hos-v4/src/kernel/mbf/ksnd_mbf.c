/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static void kernel_sch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
						T_KERNEL_MBFCB_RAM *mbfcb_ram, UB chr);	/* １キャラクタ送信 */



/* メッセージバッファへの送信 */
ER kernel_snd_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		VP                       msg,			/* 送信メッセージの先頭番地 */
		UINT                     msgsz)			/* 送信メッセージのサイズ(バイト数) */
{
	T_MKNL_TCB *mtcb;
	SIZE       fresz;
	SIZE       tail;
	INT        i;

	/* 送信待ちタスクをチェック */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* 送信待ち行列の先頭タスクを参照 */
	if ( mtcb != NULL )
	{
		return E_TMOUT;		/* 送信待ちが既にあればタイムアウト */
	}

	/* 受信待ちタスクチェック */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* 受信待ち行列の先頭タスクを参照 */
	if ( mtcb != NULL )
	{
		/* 受信タスクの待ちを解除 */
		__hos_bcopy((VP)mtcb->data, msg, msgsz);		/* データコピー */
		mknl_rmv_que(mtcb);						/* 待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, (ER_UINT)msgsz);		/* タスクの待ち解除 */

		return E_OK;	/* 正常完了 */
	}

	/* 空きサイズチェック */
	if ( mbfcb_ram->fmbfsz < msgsz + sizeof(UINT) )
	{
		return E_TMOUT;		/* タイムアウト */
	}
	
	/* サイズ送信 */
	for ( i = sizeof(UINT) - 1; i >= 0; i-- )
	{
		/* 上位から順に8bit単位で書き込み */
		kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)((msgsz >> (i * 8)) & 0xff));
	}

	/* 末尾位置算出 */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* データ送信 */
	fresz = (UINT)mbfcb_rom->mbfsz - tail;	/* バッファ折り返しまでの空きサイズ算出 */
	if ( fresz >= msgsz )					/* 折り返し不要か判定 */
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, msgsz);				/* データコピー */
	}
	else
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, fresz);				/* 折り返し点までコピー */
		__hos_bcopy((UB *)mbfcb_rom->mbf, (UB *)msg + fresz, msgsz - fresz);	/* 残りを先頭からコピー */
	}

	/* 空きサイズ更新 */
	mbfcb_ram->fmbfsz -= msgsz;

	/* 送信個数インクリメント */
	mbfcb_ram->smsgcnt++;

	return E_OK;
}


/* １キャラクタ送信 */
void kernel_sch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		UB                       chr)			/* 送信するキャラクタ */
{
	SIZE tail;

	/* 末尾位置算出 */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* １キャラクタ送信 */
	*((UB *)mbfcb_rom->mbf + tail) = chr;

	/* バッファ空きサイズ更新 */
	mbfcb_ram->fmbfsz--;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
