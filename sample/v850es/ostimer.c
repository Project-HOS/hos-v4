/********************************************************************************/
/*	Hyper Operating System V4  サンプルプログラム								*/
/*		OS タイマ																*/
/*																				*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/********************************************************************************/
#pragma		ioreg

#include	"kernel.h"
#include	"kernel_id.h"
#include	"ostimer.h"
#include	<stdio.h>

#if 1	// 1 == WDTI をOSタイマにする。 0 == TMM をOSタイマにする。
/*
 *	OS用タイマ初期化
 *		INTWTI, INTWT を使用しています。
 *		include/v850es/vect.h と vectasm.inc にてベクタ番号を定義しています。
 */
void	ostim_init(VP_INT exinf)
{
	WTM		= 0x00;					/* WT ストップ								*/
	PRSM0	= 0x00;					/* fBRG=fx(5MHz, 200nsec.)					*/
	PRSCM0	= 0x4D;					/* プリスケーラレジスタ = 5MHz/32.768kHz/2	*/
	WTIC	= 0x47;					/* 割込みレベル 7							*/
	WTIIC	= 0x41;					/* 割込みレベル 1							*/
	WTM		|= 0x08;				/* 時計用フラグのセット 2^5/fBRG			*/
	WTM		|= 0x90;				/* インタバルタイマプリスケーラ 2^5/fBRG	*/
	BGCE0	= 1;					/* 時計タイマ動作許可						*/
	WTIF	= 0;					/* WTIF クリア								*/
	WTMK	= 1;					/* WT 割込み禁止							*/
	WTIIF	= 0;					/* WTIIF クリア								*/
	WTIMK	= 0;					/* WTI 割込み許可							*/
	WTM		|= 0x03;
}
void	wdt_hdr(VP_INT exinf)
{
	WTIF	= 0;					/* WTIF クリア								*/
}
/*
 *	OSタイマ用ハンドラ
 */
void	ostim_hdr(VP_INT exinf)
{
	WTIIF	= 0;					/* WTIIF クリア								*/
	isig_tim();						/* タイムティックの供給						*/
#ifdef	DEBUG
	PCT.6 ^= 1;						/* LED1反転	(Interface付録基板用)			*/
#endif
}
#else
/*
 *	OS用タイマ初期化
 *		INTTM0 カウンタを使用しています。
 *		include/v850es/vect.h と vectasm.inc にてベクタ番号を定義しています。
 */
void	ostim_init(VP_INT exinf)
{
	TM0CE		= 0;				/* TM0CTL0.7：TMM0動作禁止					*/
	TM0EQIC0	= 0x41;				/* INTTM0EQ0割込み優先レベル：1				*/
	TM0CTL0		= 0x02;				/* 内部カウント・クロック設定：fxx/4		*/
	TM0CMP0		= (1000*20/4)-1;	/* インターバル時間：1msec					*/
	TM0EQMK0	= 0;				/* INTTM0 割込み許可						*/
	TM0CE		= 1;				/* TMM0 インターバルタイマ動作許可			*/
}
/*
 *	OSタイマ用ハンドラ
 */
void	ostim_hdr(VP_INT exinf)
{
	isig_tim();						/* タイムティックの供給						*/
#ifdef	DEBUG
	PCT.6 ^= 1;						/* LED1反転	(Interface付録基板用)			*/
#endif
}
#endif
/*	---------------------------------------------------------------------------	*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
