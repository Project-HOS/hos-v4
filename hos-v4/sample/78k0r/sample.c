/********************************************************************************/
/* Hyper Operating System V4  サンプルプログラム								*/
/*																				*/
/*	各タスクの起動時刻とタスク名をシリアルコンソールへ表示するプログラム		*/
/*		タスク名	優先度	起動条件											*/
/*		Task1		1		Task2からのsig_sem()により起動						*/
/*		Task2		2		1[s]おきの周期タイマにより起動						*/
/*																				*/
/*										Copyright (C) 1998-2009 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/********************************************************************************/
#pragma		sfr
#pragma		nop

#include	"kernel.h"
#include	"kernel_id.h"
#include	"sample.h"
#include	"hosdenv.h"
#include	<stdio.h>

/*	--------------------------------------------------------------------------	*/
/*	-	UART2 に１文字送信													 -	*/
/*	--------------------------------------------------------------------------	*/
void	uart2_putc(
	uint8	x
)
{
#if	1						/* 改行文字を２文字化。　不要なら、1 -> 0 に	*/
	if( x == '\n' ) {
		while( (SSR10 & 0x0020) != 0 ) ;
		TXD2 = '\r';
	}
#endif
	while( (SSR10 & 0x0020) != 0 ) ;
	TXD2 = x;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UART2 より１文字受信												 -	*/
/*	--------------------------------------------------------------------------	*/
uint8	uart2_getc( void )
{
	uint8	rxd;

	while( (SSR11 & 0x0020) == 0 ) ;
	rxd = RXD2;
	return rxd;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UART2 に文字列送信													 -	*/
/*	--------------------------------------------------------------------------	*/
void	uart2_puts(
	int8	*x
)
{
	for( ; *x != 0; x++ ) {
#if	1						/* 改行文字を２文字化。　不要なら、1 -> 0 に	*/
		if( *x == '\n' ) {
			while( (SSR10 & 0x0020) != 0 ) ;
			TXD2 = '\r';
		}
#endif
		while( (SSR10 & 0x0020) != 0 ) ;
		TXD2 = *x;
	}
}
/*	--------------------------------------------------------------------------	*/
/*	-	UART2 初期化														 -	*/
/*	-		Baudrate	= 38400bps											 -	*/
/*	-		Character	= 8 bit												 -	*/
/*	-		Parity		= NONE												 -	*/
/*	-		Stop Bit	= 1 bit												 -	*/
/*	-		※　送受信における割込み処理は実施しない						 -	*/
/*	--------------------------------------------------------------------------	*/
void	init_UART2( void )
{
	SAU1EN	= 1;			/* SAU1 clock supply								*/
	NOP();
	NOP();
	NOP();
	NOP();
	SPS1	= 0x0022;		/* CK11=CK10=fclk/(2^2)=5MHz						*/

	/* UART2 initial setting */
	ST1		|= 0b00000011;	/* disable UART2 RxD and UART2 TxD					*/
	SRMK2	= 1;			/* disable interrupt of INTSR2						*/
	SREMK2	= 1;			/* disable interrupt of INTSRE2						*/
	STMK2	= 1;			/* disable interrupt of INTST2						*/
	SRIF2	= 0;			/* clear interrupt-flag of INTSR2					*/
	SREIF2	= 0;			/* clear interrupt-flag of INTSRE2					*/
	STIF2	= 0;			/* clear interrupt-flag of INTST2					*/
	SIR11	= 0b00000111;	/* clear Flaming-E/F, Parity-E/F, Overrun-E/F		*/
	NFEN0	|= 0b00010000;	/* noise filter on for UART2 RxD					*/
	// RxD
	SMR11	= 0x8122;		/* CKS=1, CCS=0, STS=1, SIS=0, MD=UART				*/
	SCR11	= 0x4097;		/* RxD(TXE=0, RXE=1), 8N1, LSB-1st					*/
	SDR11	= 0x8000;		/* SDR[15:9]=64 -> 64 << 9 = 0x8000					*/
	// TxD
	SMR10	= 0x0022;		/* CKS=0, CCS=0, STS=0, SIS=0, MD=UART				*/
	SCR10	= 0x8097;		/* TxD(TXE=1, RXE=0), 8N1, LSB-1st					*/
	SDR10	= 0x8000;		/* SDR[15:9]=64 -> 64 << 9 = 0x8000					*/
	SO1		|= 0x0001;		/* output level										*/
	SOE1	|= 0x0001;		/* enable UART2 output								*/

	/* RXD2 pin setting */
	PM14	|= 0x08;
	/* TxD2 pin setting */
	P14		|= 0x10;
	PM14	&= ~0x10;

	SS1		|= 0b00000011;	/* enable UART2 RxD and UART2 TxD					*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	CPU初期化															 -	*/
/*	--------------------------------------------------------------------------	*/
void	init_CPU( void )
{
	OSTS	= 0b00000111;			/* 13.11msec. waiting (2^18/fx)				*/
	CMC		= 0b01000001;			/* 20MHz, X1 mode, non-SubCLK				*/
	MSTOP	= 0;					/* start external CLK with X1				*/
	while((OSTC & 0xFF) != 0xFF) ;	/* X1 CLK 安定待ち							*/
	OSMC	= 1;					/* >10MHz									*/
	CKC		= 0b00111000;			/* CSS=0, MCM0=1, fCLK=fMX					*/
	HIOSTOP	= 1;					/* stop internal HighSpeed CLK				*/
	XTSTOP	= 1;					/* stop SubCLK								*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	以下、定番のサンプル。												 -	*/
/*	--------------------------------------------------------------------------	*/
/**
 *  main関数
 */
int		main( void )
{
	init_CPU();						/* PLL による逓倍クロック動作				*/
	init_UART2();					/* UART0 初期化								*/

	PM7.6	= 0;					/* LED1 : 出力モード						*/
	PM7.7	= 0;					/* LED2 : 出力モード						*/
	P7.6	= 0;					/* LED1 : 0=点灯, 1=消灯					*/
	P7.7	= 0;					/* LED2 : 0=点灯, 1=消灯					*/
	uart2_getc();
	uart2_puts("\nWelcome to HOSv4 on 78K0R !\n");
	P7.6	= 1;					/* LED1 : 0=点灯, 1=消灯					*/
	P7.7	= 1;					/* LED2 : 0=点灯, 1=消灯					*/

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

	uart2_putc( '0' | (uint8)(st.ltime / 10000) % 10 );
	uart2_putc( '0' | (uint8)(st.ltime /  1000) % 10 );
	uart2_putc( '0' | (uint8)(st.ltime /   100) % 10 );
	uart2_putc( '0' | (uint8)(st.ltime /    10) % 10 );
	uart2_putc( '0' | (uint8)(st.ltime /     1) % 10 );
	uart2_putc( ':' );
	uart2_putc( 'T' );
	uart2_putc( 'a' );
	uart2_putc( 's' );
	uart2_putc( 'k' );
	uart2_putc( ' ' );
	uart2_putc( '0' | (uint8)no );
	uart2_putc( '\n' );
}
/**
 *  サンプルタスク1
 *  - タスク2がセマフォを解除するまで待つ
 *  - 現在時刻とタスク名を表示
 */
void	sample_task_1( VP_INT exinf )
{
	int		i;

	for( i = 0; ; i++ ) {
		wai_sem (SEMID_SAMPLE_1);
		sample_print( 1 );

		P7.6 = i & 1;				/* LED1 : 0=点灯, 1=消灯					*/
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
	int		i;

	for( i = 1; ; i++ ) {
		slp_tsk ();
		sig_sem (SEMID_SAMPLE_1);
		sample_print( 2 );

		P7.7 = i & 1;				/* LED2 : 0=点灯, 1=消灯					*/
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
/*										Copyright (C) 1998-2009 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
