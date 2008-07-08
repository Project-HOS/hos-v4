/*******************************************************************************
 * Hyper Operating System V4  サンプルプログラム
 *
 *      例外処理サンプル
 *
 *                                      Copyright (C) 1998-2008 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/

#include <semb1200a/semb1200a.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"
#include "irq_sample.h"
/**
 *  例外処理利用のための設定（適宜設定）
 */
/* SEMB1200A 専用 */
// #define __USE_IP2_CH9_PWM0__
// #define __USE_IP2_CH9_PWM1__
// #define __USE_IP2_CH9_PWM2__
// #define __USE_IP2_CH9_PWM3__
// #define __USE_IP2_CH9_UART30__
// #define __USE_IP2_CH9_UART31__
// #define __USE_IP2_CH9_UART32__
// #define __USE_IP2_CH9_UART33__
// #define __USE_IP2_CH9_UART34__
// #define __USE_IP2_CH9_UART35__
// #define __USE_IP2_CH9_UART36__
// #define __USE_IP2_CH9_UART37__
/* VR9721, UX1200E 用 */
#define	__USE_IP2_CH6_TC0__
// #define __USE_IP2_CH6_TC1__
// #define __USE_IP2_CH6_TC2__
// #define __USE_IP2_CH6_TC3__
// #define __USE_IP2_CH6_TC4__
// #define __USE_IP2_CH6_TC5__
// #define __USE_IP2_CH6_TC6__
// #define __USE_IP2_CH6_TC7__
// #define __USE_IP2_CH5_CSI__
// #define __USE_IP2_CH5_CSI_EMPTY__
// #define __USE_IP2_CH5_CSI_OVERFLOW__
// #define __USE_IP2_CH5_UART1__
// #define __USE_IP2_CH5_UART1_TIMEOUT__
// #define __USE_IP2_CH5_UART2_TIMEOUT__
/**
 *  例外処理利用のための設定（変更不要）
 */
#if	(defined __USE_IP2_CH9_PWM0__) || (defined __USE_IP2_CH9_PWM1__) \
	|| (defined __USE_IP2_CH9_PWM2__) || (defined __USE_IP2_CH9_PWM3__)
#define	__USE_IP2_CH9_PWM__
#endif
#if (defined __USE_IP2_CH9_UART30__) || (defined __USE_IP2_CH9_UART31__) \
	|| (defined __USE_IP2_CH9_UART32__) || (defined __USE_IP2_CH9_UART33__) \
	|| (defined __USE_IP2_CH9_UART34__) || (defined __USE_IP2_CH9_UART35__) \
	|| (defined __USE_IP2_CH9_UART36__) || (defined __USE_IP2_CH9_UART37__)
#define	__USE_IP2_CH9_UART3__
#endif
#if	(defined __USE_IP2_CH9_PWM__) || (defined __USE_IP2_CH9_UART3__)
#define	__USE_IP2_CH9__
#endif
#if	(defined __USE_IP2_CH6_TC0__) || (defined __USE_IP2_CH6_TC1__) \
	|| (defined __USE_IP2_CH6_TC2__) || (defined __USE_IP2_CH6_TC3__) \
	|| (defined __USE_IP2_CH6_TC4__) || (defined __USE_IP2_CH6_TC5__) \
	|| (defined __USE_IP2_CH6_TC6__) || (defined __USE_IP2_CH7_TC1__)
#define	__USE_IP2_CH6__
#endif
#if	(defined __USE_IP2_CH5_CSI__) \
	|| (defined __USE_IP2_CH5_CSI_EMPTY__) || (defined __USE_IP2_CH5_CSI_OVERFLOW__)\
	|| (defined __USE_IP2_CH5_UART1__) || (defined __USE_IP2_CH5_UART1_TIMEOUT__) \
	|| (defined __USE_IP2_CH5_UART2__) || (defined __USE_IP2_CH5_UART2_TIMEOUT__)
#define	__USE_IP2_CH5__
#endif
/**
 *  例外処理初期化(External INT2)
 */
void
int2_init(VP_INT exinf)
{
	//
	//	プリスケーラ PRE_A の設定 (TC#0-#7 すべて PRE_A を使う例です）
	//
	io_out16( PRE_A, 0x0004 | 0x0002 | 0x0000 );	// RATE=1/25, EN=1, CKSEL=25MHz
	io_out16( CLK_SEL_A, 0x0000 );					// TC#0,TC#1,TC#2,TC#3 = prescaler-CH-A clk
	io_out16( CLK_SEL_B, 0x0000 );					// TC#4,TC#5,TC#6,TC#7 = prescaler-CH-A clk
#ifndef __USE_IP2_CH6_TC0__
	io_or16( CLK_SEL_A, 0x0007 );					// TC#0 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC1__
	io_or16( CLK_SEL_A, 0x0070 );					// TC#1 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC2__
	io_or16( CLK_SEL_A, 0x0700 );					// TC#2 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC3__
	io_or16( CLK_SEL_A, 0x7000 );					// TC#3 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC4__
	io_or16( CLK_SEL_B, 0x0007 );					// TC#4 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC5__
	io_or16( CLK_SEL_B, 0x0070 );					// TC#5 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC6__
	io_or16( CLK_SEL_B, 0x0700 );					// TC#6 = fixed LowLevel
#endif
#ifndef __USE_IP2_CH6_TC7__
	io_or16( CLK_SEL_B, 0x7000 );					// TC#7 = fixed LowLevel
#endif
	//
	//	Timer_TC#0 割込み
	//
#ifdef	__USE_IP2_CH6_TC0__
	io_out16( TC0_DATA0, 50000U );			// compare match = 50.0msec
	io_out16( TC0_STS, 0x0002 );			// TC0_DATA0 値を比較値として指定
	io_out16( TC0_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC0_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#1 割込み
	//
#ifdef	__USE_IP2_CH6_TC1__
	io_out16( TC1_DATA0, 2000U );			// compare match = 2.00msec
	io_out16( TC1_STS, 0x0002 );			// TC1_DATA0 値を比較値として指定
	io_out16( TC1_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC1_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#2 割込み
	//
#ifdef	__USE_IP2_CH6_TC2__
	io_out16( TC2_DATA0, 3000U );			// compare match = 3.0msec
	io_out16( TC2_STS, 0x0002 );			// TC2_DATA0 値を比較値として指定
	io_out16( TC2_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC2_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#3 割込み
	//
#ifdef	__USE_IP2_CH6_TC3__
	io_out16( TC3_DATA0, 4000U );			// compare match = 4.0msec
	io_out16( TC3_STS, 0x0002 );			// TC3_DATA0 値を比較値として指定
	io_out16( TC3_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC3_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#4 割込み
	//
#ifdef	__USE_IP2_CH6_TC4__
	io_out16( TC4_DATA0, 5000U );			// compare match = 5.0msec
	io_out16( TC4_STS, 0x0002 );			// TC4_DATA0 値を比較値として指定
	io_out16( TC4_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC4_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#5 割込み
	//
#ifdef	__USE_IP2_CH6_TC5__
	io_out16( TC5_DATA0, 6000U );			// compare match = 6.0msec
	io_out16( TC5_STS, 0x0002 );			// TC5_DATA0 値を比較値として指定
	io_out16( TC5_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC5_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#6 割込み
	//
#ifdef	__USE_IP2_CH6_TC6__
	io_out16( TC6_DATA0, 7000U );			// compare match = 7.0msec
	io_out16( TC6_STS, 0x0002 );			// TC6_DATA0 値を比較値として指定
	io_out16( TC6_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC6_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	Timer_TC#7 割込み
	//
#ifdef	__USE_IP2_CH6_TC7__
	io_out16( TC7_DATA0, 8000U );			// compare match = 8.0msec
	io_out16( TC7_STS, 0x0002 );			// TC7_DATA0 値を比較値として指定
	io_out16( TC7_STS, 0x0040 | 0x0020 );	// CLRCNT=1;      タイマカウンタのクリア
											// INTCONT = 1;   割込み要求クリア
	io_out16( TC7_EN, 0x0002 | 0x0001 );	// INT_EN=1, CNT_EN=1
#endif
	//
	//	割込みマスク・レベル設定（スタート）
	//
	io_out16( INTC_LEVEL_EDGE, 0x0000 );	// level 検出モード
	io_out16( INTC_LEVEL_MASK, 0 );			// mask なし
#ifdef	__USE_IP2_CH9__
	io_out16( INTC_CH9_LEVEL, 15 );			// level=15 : IP2_CH9
	io_or16( INTC_INT_MASK, 0x0100 );		// 割り込みマスク指定（割り込み許可）
#endif
#ifdef	__USE_IP2_CH6__
	io_out16( INTC_CH6_LEVEL, 14 );			// level=14 : IP2_CH6
	io_or16( INTC_INT_MASK, 0x0020 );		// 割り込みマスク指定（割り込み許可）
#endif
#ifdef	__USE_IP2_CH5__
	io_out16( INTC_CH5_LEVEL, 13 );			// level=13 : IP2_CH5
	io_or16( INTC_INT_MASK, 0x0010 );		// 割り込みマスク指定（割り込み許可）
#endif
}
/**
 *  例外処理本体 (External INT2)
 */
int		flag_tc0 = 0;
int		cnt_tc0 = 0;

void
int2_main (VP_INT exinf)
{
	unsigned short	int2_stat;
	unsigned short	unit_stat;

	io_out16( INTC_INT_ACK, 0 );
	int2_stat = io_in16( INTC_INT_PENDING );
#ifdef	__USE_IP2_CH9__
	if( int2_stat & (1 << 8) ) {					// CH9 割込み
#ifdef	__USE_IP2_CH9_PWM0__
		unit_stat = pwm_unit_get(0, SEMB1200_PWM_INT_STAT2);
		if( unit_stat ) {
			pwm_unit_set( 0, SEMB1200_PWM_INT_PEND2, 1 );
			// ここに処理したい内容を記述する
			pwm_unit_set( 0, SEMB1200_PWM_INT_MASK2, 0 );
		}
#endif
#ifdef	__USE_IP2_CH9_PWM1__
		unit_stat = pwm_unit_get(1, SEMB1200_PWM_INT_STAT2);
		if( unit_stat ) {
			pwm_unit_set( 1, SEMB1200_PWM_INT_PEND2, 1 );
			// ここに処理したい内容を記述する
			pwm_unit_set( 1, SEMB1200_PWM_INT_MASK2, 0 );
		}
#endif
#ifdef	__USE_IP2_CH9_PWM2__
		unit_stat = pwm_unit_get(2, SEMB1200_PWM_INT_STAT2);
		if( unit_stat ) {
			pwm_unit_set( 2, SEMB1200_PWM_INT_PEND2, 1 );
			// ここに処理したい内容を記述する
			pwm_unit_set( 2, SEMB1200_PWM_INT_MASK2, 0 );
		}
#endif
#ifdef	__USE_IP2_CH9_PWM3__
		unit_stat = pwm_unit_get(3, SEMB1200_PWM_INT_STAT2);
		if( unit_stat ) {
			pwm_unit_set( 3, SEMB1200_PWM_INT_PEND2, 1 );
			// ここに処理したい内容を記述する
			pwm_unit_set( 3, SEMB1200_PWM_INT_MASK2, 0 );
		}
#endif
#ifdef	__USE_IP2_CH9_UART3__
		unit_stat = io_in16( UART3_INTSTS );
#endif
#ifdef	__USE_IP2_CH9_UART30__
		if( unit_stat & (1 << 0) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 0) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART31__
		if( unit_stat & (1 << 1) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 1) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART32__
		if( unit_stat & (1 << 2) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 2) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART33__
		if( unit_stat & (1 << 3) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 3) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART34__
		if( unit_stat & (1 << 4) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 4) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART35__
		if( unit_stat & (1 << 5) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 5) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART36__
		if( unit_stat & (1 << 6) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 6) );
		}
#endif
#ifdef	__USE_IP2_CH9_UART37__
		if( unit_stat & (1 << 7) ) {
			// ここに処理したい内容を記述する
			io_out16( UART3_INTSTS, (1 << 7) );
		}
#endif
		io_out16( INTC_INT_CLR, (1 << 8) );		// CH9 割込みクリア
	}
#endif
#ifdef	__USE_IP2_CH6__
	if( int2_stat & (1 << 5) ) {				// CH6 割込み
#ifdef	__USE_IP2_CH6_TC0__
		unit_stat = io_in16( TC0_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
#if 1	// demo
			cnt_tc0++;
			if( cnt_tc0 >= 100 ) {
				cnt_tc0 = 0;
				flag_tc0++;
			}
#endif
			io_out16( TC0_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC1__
		unit_stat = io_in16( TC1_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC1_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC2__
		unit_stat = io_in16( TC2_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC2_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC3__
		unit_stat = io_in16( TC3_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC3_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC4__
		unit_stat = io_in16( TC4_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC4_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC5__
		unit_stat = io_in16( TC5_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC5_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC6__
		unit_stat = io_in16( TC6_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC6_STS, 0x0020 );		// INTCONT クリア
		}
#endif
#ifdef	__USE_IP2_CH6_TC7__
		unit_stat = io_in16( TC7_STS );
		if( unit_stat & 0x0020 ) {
			// ここに処理したい内容を記述する
			io_out16( TC7_STS, 0x0020 );		// INTCONT クリア
		}
#endif
		io_out16( INTC_INT_CLR, (1 << 5) );		// CH6 割込みクリア
	}
#endif
#ifdef	__USE_IP2_CH5__
	if( int2_stat & (1 << 4) ) {				// CH5 割込み
#if (defined __USE_IP2_CH5_CSI__ ) || (defined __USE_IP2_CH5_CSI_EMPTY__)
		unit_stat = io_in16( CSI_INTREG );
#endif
#ifdef	__USE_IP2_CH5_CSI__
		if( unit_stat & (1 << 15) ) {			// CSI割込み
			// ここに処理したい内容を記述する
			io_out16( CSI_INTREG, (1 << 15) );	// 割込み状態のクリア
		}
#endif
#ifdef	__USE_IP2_CH5_CSI_EMPTY__
		if( unit_stat & (1 << 8) ) {			// CSI_EMPTY割込み
			// ここに処理したい内容を記述する
			io_out16( CSI_INTREG, (1 << 8) );	// 割込み状態のクリア
		}
#endif
#ifdef	__USE_IP2_CH5_CSI_OVERFLOW__
		if( unit_stat & (1 << 0) ) {			// CSI_OVERFLOW割込み
			// ここに処理したい内容を記述する
			io_out16( CSI_INTREG, (1 << 0) );	// 割込み状態のクリア
		}
#endif
#if (defined __USE_IP2_CH5_UART1__) || (defined __USE_IP2_CH5_UART1_TIMEOUT__)
		unit_stat = io_in16( UART_1IIR );
#endif
#ifdef	__USE_IP2_CH5_UART1__
		if( unit_stat & (1 << 0) ) {			// UART1割込み
			// ここに処理したい内容を記述する
			io_out16( UART_1IIR, (1 << 0) );	// 割込み状態のクリア
		}
#endif
#ifdef	__USE_IP2_CH5_UART1_TIMEOUT__
		if( unit_stat & (1 << 3) ) {			// UART1 TimeOut 割込み
			// ここに処理したい内容を記述する
			io_out16( UART_1IIR, (1 << 3) );	// 割込み状態のクリア
		}
#endif
#if (defined __USE_IP2_CH5_UART1__) || (defined __USE_IP2_CH5_UART1_TIMEOUT__)
		unit_stat = io_in16( UART_2IIR );
#endif
#ifdef	__USE_IP2_CH5_UART2__
		if( unit_stat & (1 << 0) ) {			// UART2割込み
			// ここに処理したい内容を記述する
			io_out16( UART_2IIR, (1 << 0) );	// 割込み状態のクリア
		}
#endif
#ifdef	__USE_IP2_CH5_UART2_TIMEOUT__
		if( unit_stat & (1 << 3) ) {			// UART2 TimeOut 割込み
			// ここに処理したい内容を記述する
			io_out16( UART_2IIR, (1 << 3) );	// 割込み状態のクリア
		}
#endif
		io_out16( INTC_INT_CLR, (1 << 4) );		// CH5割込みクリア
	}
#endif
}
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
