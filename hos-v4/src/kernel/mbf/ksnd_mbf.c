/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



static void kernel_sch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
						T_KERNEL_MBFCB_RAM *mbfcb_ram, UB chr);	/* １キャラクタ送信 */



/* メッセージバッファへの送信 */
ER kernel_snd_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		VP                       msg,			/* 送信メッセージの先頭番地 */
		UINT                     msgsz)			/* 送信メッセージのサイズ(バイト数) */
{
	UINT fresz;

	/* 空きサイズ算出 */
	if ( mbfcb_ram->head > mbfcb_ram->tail )
	{
		fresz = mbfcb_ram->head - mbfcb_ram->tail - 1;
	}
	else
	{
		fresz = (UINT)mbfcb_rom->mbfsz - (mbfcb_ram->tail - mbfcb_ram->head) - 1;
	}
	
	/* 送信可能判定 */
	if ( fresz < msgsz + 2 )
	{
		return E_TMOUT;		/* タイムアウト */
	}
	
	/* サイズ送信 */
	kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)(msgsz / 256));
	kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)(msgsz % 256));

	/* データ送信 */
	fresz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->tail;	/* バッファ折り返しまでの空きサイズ算出 */
	if ( fresz >= msgsz )								/* 折り返し不要か判定 */
	{
		memcpy((UB *)mbfcb_rom->mbf + mbfcb_ram->tail, msg, msgsz);		/* データコピー */
	}
	else
	{
		memcpy((UB *)mbfcb_rom->mbf + mbfcb_ram->tail, msg, fresz);		/* 折り返し点までコピー */
		memcpy((UB *)mbfcb_rom->mbf, (UB *)msg + fresz, msgsz - fresz);	/* 残りを先頭からコピー */
	}

	/* ポインタ更新 */
	mbfcb_ram->tail += msgsz;
	if ( mbfcb_ram->tail >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->tail -= (UINT)mbfcb_rom->mbfsz;
	}

	return E_OK;
}


/* １キャラクタ送信 */
void kernel_sch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		UB                       chr)			/* 送信するキャラクタ */
{
	/* １キャラクタ送信 */
	*((UB *)mbfcb_rom->mbf + mbfcb_ram->tail) = chr;

	/* ポインタ更新 */
	if ( mbfcb_ram->tail + 1 < (UINT)mbfcb_rom->mbfsz )
	{
		mbfcb_ram->tail++;
	}
	else
	{
		mbfcb_ram->tail = 0;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
