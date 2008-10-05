/********************************************************************************/
/* Hyper Operating System V4  ����ץ�ץ����								*/
/*																				*/
/*	�ƥ������ε�ư����ȥ�����̾�򥷥ꥢ�륳�󥽡����ɽ������ץ����		*/
/*		������̾	ͥ����	��ư���											*/
/*		Task1		1		Task2�����sig_sem()�ˤ�굯ư						*/
/*		Task2		2		1[s]�����μ��������ޤˤ�굯ư						*/
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
/*	-	UARTA0 �ˣ�ʸ������													 -	*/
/*	--------------------------------------------------------------------------	*/
void	uarta0_putc(
	int		x
)
{
#if	1						/* ����ʸ����ʸ�����������פʤ顢1 -> 0 ��	*/
	if( x == '\n' ) {
		while( UA0STR.7 == 1 ) ;
		UA0TX = '\r';
	}
#endif
	while( UA0STR.7 == 1 ) ;
	UA0TX = x;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UARTA0 ��꣱ʸ������												 -	*/
/*	--------------------------------------------------------------------------	*/
uint8	uarta0_getc( void )
{
	while( UA0STR & 0x07 != 0 ) ;
	return UA0RX;
}
/*	--------------------------------------------------------------------------	*/
/*	-	UARTA0 �����														 -	*/
/*	-		Baudrate	= 38400bps											 -	*/
/*	-		Character	= 8 bit												 -	*/
/*	-		Parity		= NONE												 -	*/
/*	-		Stop Bit	= 1 bit												 -	*/
/*	-		�����������ˤ��������߽����ϼ»ܤ��ʤ�						 -	*/
/*	--------------------------------------------------------------------------	*/
void	init_uarta0( void )
{
	PF3L.0		= 0;				/* P30 : UARTA0 TxD �Ρ��ޥ�⡼��			*/
	PF3L.1		= 0;				/* P31 : UARTA0 RxD �Ρ��ޥ�⡼��			*/
	PFC3L.0		= 0;				/* P30 : UARTA0 TxD ü������				*/
	PFC3L.1		= 0;				/* P31 : UARTA0 RxD ü������				*/
	PMC3L.0		= 1;				/* P30 : UARTA0 TxD ��ǽü������			*/
	PMC3L.1		= 1;				/* P31 : UARTA0 RxD ��ǽü������			*/

	UA0TXE		= 0;				/* UARTA0 �����ػ�							*/
	UA0RXE		= 0;				/* UARTA0 �����ػ�							*/
	UA0PWR		= 0;				/* UARTA0 ư��ػ�							*/
	UA0TMK		= 1;				/* UARTA0 TxD ����߶ػ�					*/
	UA0RMK		= 1;				/* UARTA0 RxD ����߶ػ�					*/
	UA0CTL0		= 0b00010010;		/* LSB/Parity=NON/8bit/STOP=1bit			*/
	UA0OPT0		= 0x14;				/* �������ǡ�����ȿž						*/
	UA0CTL1		= 0x01;				/* baudrate 38400bps						*/
	UA0CTL2		= 0x82;				/* baudrate 38400bps						*/
	UA0RIC		= 0b01000111;		/* INT_RxD priority = 7						*/
	UA0TIC		= 0b01000111;		/* INT_TxD priority = 7						*/
	UA0PWR		= 1;				/* UARTA0 ư�����							*/
	UA0TXE		= 1;				/* UARTA0 ��������							*/
	UA0RXE		= 1;				/* UARTA0 ��������							*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	CPU�����															 -	*/
/*	-		PLL �ˤ�����ܽ����μ»�										 -	*/
/*	-		������Ǥ� ����5MHz ������ 20MHz �� 4����)						 -	*/
/*	--------------------------------------------------------------------------	*/
int		init_CPU( void )
{
	extern uint32	_S_romp;

	VSWC	= 1;					/* �����ƥ०�����ȥ���ȥ���쥸����		*/
	WDTM2	= 0;					/* WDTMư��ػ�								*/
	__asm( "mov		0x00, r11" );
	__asm( "st.b	r11, PRCMD" );	/* ����쥸������������PMCMD�˽񤭹���		*/
	__asm( "st.b	r11, PCC" );	/* PCC������ PCC = 00:						*/
	while( LOCK );					/* 1:UnLock��0:Lock -> ���ȿ������Ԥ�		*/
	SELPLL	= 1;					/* 1:PLLư�� 0:PLL���						*/
	return _rcopy(&_S_romp, -1);	/* ROM������								*/
}
/*	--------------------------------------------------------------------------	*/
/*	-	�ʲ������֤Υ���ץ롣��mips ��Ʊ��									 -	*/
/*	--------------------------------------------------------------------------	*/
/**
 *  main�ؿ�
 */
int		main( void )
{
	init_CPU();						/* PLL �ˤ�����ܥ���å�ư��				*/
	init_uarta0();					/* UARTA0 �����							*/
#ifdef DEBUG
	PMCCT.6		= 0;				/* ���ϥ⡼��ü������						*/
	PMCT.6		= 0;				/* LED1 ���ϥݡ��Ȥ�����					*/
	PCT.6		= 0;				/* LED1�� ���� (LowActive)					*/
	{
		int		c;

		do {
			c = uarta0_getc();
		} while( c != ' ' );
	}
	PCT.6		= 1;				/* LED1�� ���� (LowActive)					*/
#endif
	/* HOS-V4 �γ��� */
	sta_hos();
	return 0;
}
/**
 *  ���߻���ȥ�����no��ɽ������
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
 *  ����ץ륿����1
 *  - ������2�����ޥե���������ޤ��Ԥ�
 *  - ���߻���ȥ�����̾��ɽ��
 */
void	sample_task_1( VP_INT exinf )
{
	for (;;) {
		wai_sem (SEMID_SAMPLE_1);
		sample_print (1);
	}
}
/**
 *  ����ץ륿����2
 *  - 1[s]�δ�sleep����
 *  - ���ޥե�����
 *  - ���߻���ȥ�����̾��ɽ��
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
 *  ������ؿ�
 *  �������ε�ư��Ԥ�
 */
void	sample_init( VP_INT exinf )
{
	act_tsk (TSKID_SAMPLE_1);
	act_tsk (TSKID_SAMPLE_2);
	/* ���������ޤε�ư */
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
