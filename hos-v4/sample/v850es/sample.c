/********************************************************************************/
/* Hyper Operating System V4  サンプルプログラム								*/
/*																				*/
/*	各タスクの起動時刻とタスク名をシリアルコンソールへ表示するプログラム		*/
/*		タスク名	優先度	起動条件											*/
/*		Task1		1		Task2からのsig_sem()により起動						*/
/*		Task2		2		1[s]おきの周期タイマにより起動						*/
/*																				*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/********************************************************************************/
#pragma		ioreg

#include	"kernel.h"
#include	"kernel_id.h"
#include	"sample.h"
#include	<stdio.h>

/*	--------------------------------------------------------------------------	*/
/*	-	UARTA0 に１文字送信													 -	*/
/*	--------------------------------------------------------------------------	*/
void	uarta0_putc(
	int		x
)
{
#if	1						/* 改行文字を２文字化。　不要なら、1 -> 0 に	*/
	if( x == '\n' ) {
		while( UA0STR.7 == 1 ) ;
		UA0TX = '\r';
	}
#endif
	while( UA0STR.7 == 1 ) ;
	UA0TX = x;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UARTA0 より１文字受信												 -	*/
/*	--------------------------------------------------------------------------	*/
uint8	uarta0_getc( void )
{
	while( UA0STR & 0x07 != 0 ) ;
	return UA0RX;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UARTA0 初期化														 -	*/
/*	-		Baudrate	= 38400bps											 -	*/
/*	-		Character	= 8 bit												 -	*/
/*	-		Parity		= NONE												 -	*/
/*	-		Stop Bit	= 1 bit												 -	*/
/*	-		※　送受信における割込み処理は実施しない						 -	*/
/*	--------------------------------------------------------------------------	*/
void	init_uarta0( void )
{
	PF3L.0		= 0;				/* P30 : UARTA0 TxD ノーマルモード			*/
	PF3L.1		= 0;				/* P31 : UARTA0 RxD ノーマルモード			*/
	PFC3L.0		= 0;				/* P30 : UARTA0 TxD 端子設定				*/
	PFC3L.1		= 0;				/* P31 : UARTA0 RxD 端子設定				*/
	PMC3L.0		= 1;				/* P30 : UARTA0 TxD 機能端子設定			*/
	PMC3L.1		= 1;				/* P31 : UARTA0 RxD 機能端子設定			*/

	UA0TXE		= 0;				/* UARTA0 送信禁止							*/
	UA0RXE		= 0;				/* UARTA0 受信禁止							*/
	UA0PWR		= 0;				/* UARTA0 動作禁止							*/
	UA0TMK		= 1;				/* UARTA0 TxD 割込み禁止					*/
	UA0RMK		= 1;				/* UARTA0 RxD 割込み禁止					*/
	UA0CTL0		= 0b00010010;		/* LSB/Parity=NON/8bit/STOP=1bit			*/
	UA0OPT0		= 0x14;				/* 送受信データ非反転						*/
	UA0CTL1		= 0x01;				/* baudrate 38400bps						*/
	UA0CTL2		= 0x82;				/* baudrate 38400bps						*/
	UA0RIC		= 0b01000111;		/* INT_RxD priority = 7						*/
	UA0TIC		= 0b01000111;		/* INT_TxD priority = 7						*/
	UA0PWR		= 1;				/* UARTA0 動作許可							*/
	UA0TXE		= 1;				/* UARTA0 送信許可							*/
	UA0RXE		= 1;				/* UARTA0 受信許可							*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	CPU初期化															 -	*/
/*	-		PLL による逓倍処理の実施										 -	*/
/*	-		下記例では 外部5MHz で内部 20MHz の 4逓倍)						 -	*/
/*	--------------------------------------------------------------------------	*/
int		init_CPU( void )
{
	extern uint32	_S_romp;

	VSWC	= 1;					/* システムウェイトコントロールレジスタ		*/
	WDTM2	= 0;					/* WDTM動作禁止								*/
	__asm( "mov		0x00, r11" );
	__asm( "st.b	r11, PRCMD" );	/* 特定レジスタ使用前にPMCMDに書き込む		*/
	__asm( "st.b	r11, PCC" );	/* PCCの設定 PCC = 00:						*/
	while( LOCK );					/* 1:UnLock，0:Lock -> 周波数安定待ち		*/
	SELPLL	= 1;					/* 1:PLL動作 0:PLL停止						*/
	return _rcopy(&_S_romp, -1);	/* ROM化処理								*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	以下、定番のサンプル。　mips に同じ									 -	*/
/*	--------------------------------------------------------------------------	*/
/**
 *  main関数
 */
int		main( void )
{
	init_CPU();						/* PLL による逓倍クロック動作				*/
	init_uarta0();					/* UARTA0 初期化							*/
#ifdef DEBUG
	PMCCT.6		= 0;				/* 出力モード端子設定						*/
	PMCT.6		= 0;				/* LED1 出力ポートに設定					*/
	PCT.6		= 0;				/* LED1用 点灯 (LowActive)					*/
	{
		int		c;

		do {
			c = uarta0_getc();
		} while( c != ' ' );
	}
	PCT.6		= 1;				/* LED1用 消灯 (LowActive)					*/
#endif
	/* HOS-V4 の開始 */
	sta_hos();
	return 0;
}
/**
 *  現在時刻とタスクnoを表示する
 */
void	sample_print( int no )
{
	SYSTIM st;

	get_tim (&st);

	uarta0_putc( '0'+ (st.ltime / 10000) % 10 );
	uarta0_putc( '0'+ (st.ltime /  1000) % 10 );
	uarta0_putc( '0'+ (st.ltime /   100) % 10 );
	uarta0_putc( '0'+ (st.ltime /    10) % 10 );
	uarta0_putc( '0'+ (st.ltime /     1) % 10 );
	uarta0_putc( ':' );
	uarta0_putc( 'T' );
	uarta0_putc( 'a' );
	uarta0_putc( 's' );
	uarta0_putc( 'k' );
	uarta0_putc( ' ' );
	uarta0_putc( '0' + no );
	uarta0_putc( '\n' );
}
/**
 *  サンプルタスク1
 *  - タスク2がセマフォを解除するまで待つ
 *  - 現在時刻とタスク名を表示
 */
void	sample_task_1( VP_INT exinf )
{
	for (;;) {
		wai_sem (SEMID_SAMPLE_1);
		sample_print (1);
	}
}
/**
 *  サンプルタスク2
 *  - 1[s]の間sleepする
 *  - セマフォを解除
 *  - 現在時刻とタスク名を表示
 */
void	sample_task_2( VP_INT exinf )
{
	for (;;){
		slp_tsk ();
		sig_sem (SEMID_SAMPLE_1);
		sample_print (2);
	}
}
/**
 *  初期化関数
 *  タスクの起動を行う
 */
void	sample_init( VP_INT exinf )
{
	act_tsk (TSKID_SAMPLE_1);
	act_tsk (TSKID_SAMPLE_2);
	/* 周期タイマの起動 */
	sta_cyc (CYCID_SAMPLE_1);
}
void	sample_cycle_handler( VP_INT exinf )
{
	iwup_tsk (TSKID_SAMPLE_2);
}
/*	---------------------------------------------------------------------------	*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
