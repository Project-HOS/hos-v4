/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_mbf.h"



static UB kernel_rch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
								T_KERNEL_MBFCB_RAM *mbfcb_ram);	/* １キャラクタ受信 */



/* メッセージバッファからの受信(カーネル内部関数) */
ER_UINT kernel_rcv_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* メッセージバッファコントロールブロック(ROM部) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* メッセージバッファコントロールブロック(RAM部) */
		VP                       msg)			/* 受信メッセージを格納する先頭番地 */
{
	UINT msgsz;
	UINT tmpsz;
	INT  i;

	/* メッセージ存在チェック */
	if ( mbfcb_ram->head == mbfcb_ram->tail )
	{
		return E_TMOUT;		/* タイムアウト */
	}
	
	/* サイズ受信 */
	msgsz = 0;
	for ( i = 0; i < sizeof(UINT); i++ )
	{
		/* 下位から順に8bitずつ読み出し */
		msgsz += kernel_rch_mbf(mbfcb_rom, mbfcb_ram);
		msgsz <<= 8;
	}
	
	/* データ受信 */
	tmpsz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->head;			/* 折り返し点までのサイズを算出 */
	if ( tmpsz >= msgsz )	/* 折り返し判定 */
	{
		memcpy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, msgsz);		/* データコピー */
	}
	else
	{
		memcpy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, tmpsz);		/* 折り返し点までコピー */
		memcpy((UB *)msg + tmpsz, (UB *)mbfcb_rom->mbf, msgsz - tmpsz);	/* 残りを先頭からコピー */
	}

	/* ポインタ更新 */
	mbfcb_ram->head += msgsz;
	if ( mbfcb_ram->head >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head -= (UINT)mbfcb_rom->mbfsz;
	}

	/* 送信個数デクリメント */
	mbfcb_ram->smsgcnt--;

	return E_OK;
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
	
	return chr;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
