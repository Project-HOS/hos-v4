/********************************************************************************/
/*	Hyper Operating System V4  サンプルプログラム								*/
/*		OS タイマ																*/
/*																				*/
/*										Copyright (C) 1998-2009 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/********************************************************************************/
#pragma		sfr

#include	"kernel.h"
#include	"kernel_id.h"
#include	"ostimer.h"
#include	<stdio.h>

/*
 *	OS用タイマ初期化
 *		INTTM00 カウンタを使用しています。
 *		include/78k0r/vect.h と vectasm.inc にてベクタ番号を定義しています。
 */
void	ostim_init(VP_INT exinf)
{
	TAU0EN	= 1;						/* supplies input clock			*/
	TPS0	= 0b11110000;				/* ck00-fclk, ck01-fclk/2^15	*/
	TT0		= 0b11111111;				/* TAU CH0-7 STOP_TRG_ON		*/

	TMMK00	= 1;						/* INTTM00 disabled				*/
	TMIF00	= 0;						/* INTTM00 interrupt flag clear	*/

	TMPR000 = 0;						/* Set INTTM00 high priority	*/
	TMPR100 = 0;

	TMR00	= 0x0000;
	TDR00	= 20000 - 1;				/* 20,000 = 20.0MHz * 1msec.		*/
	TOM0	&= ~0x0001;					/* combination operation mode	*/
	TOL0	&= ~0x0001;					/* timer output value			*/
	TOE0	&= ~0x0001;					/* TO00 enable operation		*/

	TMMK00	= 0;						/* INTTM00 enabled				*/
	TS0		|= 0x0001;
}
/*
 *	OSタイマ用ハンドラ
 */
void	ostim_hdr(VP_INT exinf)
{
	isig_tim();						/* タイムティックの供給						*/
}
/*	---------------------------------------------------------------------------	*/
/*										Copyright (C) 1998-2009 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
