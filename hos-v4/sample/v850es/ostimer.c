/********************************************************************************/
/*	Hyper Operating System V4  ����ץ�ץ����								*/
/*		OS ������																*/
/*																				*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/********************************************************************************/
#pragma		ioreg

#include	"kernel.h"
#include	"kernel_id.h"
#include	"ostimer.h"
#include	<stdio.h>

#if 1	// 1 == WDTI ��OS�����ޤˤ��롣 0 == TMM ��OS�����ޤˤ��롣
/*
 *	OS�ѥ����޽����
 *		INTWTI, INTWT ����Ѥ��Ƥ��ޤ���
 *		include/v850es/vect.h �� vectasm.inc �ˤƥ٥����ֹ��������Ƥ��ޤ���
 */
void	ostim_init(VP_INT exinf)
{
	WTM		= 0x00;					/* WT ���ȥå�								*/
	PRSM0	= 0x00;					/* fBRG=fx(5MHz, 200nsec.)					*/
	PRSCM0	= 0x4D;					/* �ץꥹ������쥸���� = 5MHz/32.768kHz/2	*/
	WTIC	= 0x47;					/* ����ߥ�٥� 7							*/
	WTIIC	= 0x41;					/* ����ߥ�٥� 1							*/
	WTM		|= 0x08;				/* �����ѥե饰�Υ��å� 2^5/fBRG			*/
	WTM		|= 0x90;				/* ���󥿥Х륿���ޥץꥹ������ 2^5/fBRG	*/
	BGCE0	= 1;					/* ���ץ�����ư�����						*/
	WTIF	= 0;					/* WTIF ���ꥢ								*/
	WTMK	= 1;					/* WT ����߶ػ�							*/
	WTIIF	= 0;					/* WTIIF ���ꥢ								*/
	WTIMK	= 0;					/* WTI ����ߵ���							*/
	WTM		|= 0x03;
}
void	wdt_hdr(VP_INT exinf)
{
	WTIF	= 0;					/* WTIF ���ꥢ								*/
}
/*
 *	OS�������ѥϥ�ɥ�
 */
void	ostim_hdr(VP_INT exinf)
{
	WTIIF	= 0;					/* WTIIF ���ꥢ								*/
	isig_tim();						/* ������ƥ��å��ζ���						*/
#ifdef	DEBUG
	PCT.6 ^= 1;						/* LED1ȿž	(Interface��Ͽ������)			*/
#endif
}
#else
/*
 *	OS�ѥ����޽����
 *		INTTM0 �����󥿤���Ѥ��Ƥ��ޤ���
 *		include/v850es/vect.h �� vectasm.inc �ˤƥ٥����ֹ��������Ƥ��ޤ���
 */
void	ostim_init(VP_INT exinf)
{
	TM0CE		= 0;				/* TM0CTL0.7��TMM0ư��ػ�					*/
	TM0EQIC0	= 0x41;				/* INTTM0EQ0�����ͥ���٥롧1				*/
	TM0CTL0		= 0x02;				/* ����������ȡ�����å����ꡧfxx/4		*/
	TM0CMP0		= (1000*20/4)-1;	/* ���󥿡��Х���֡�1msec					*/
	TM0EQMK0	= 0;				/* INTTM0 ����ߵ���						*/
	TM0CE		= 1;				/* TMM0 ���󥿡��Х륿����ư�����			*/
}
/*
 *	OS�������ѥϥ�ɥ�
 */
void	ostim_hdr(VP_INT exinf)
{
	isig_tim();						/* ������ƥ��å��ζ���						*/
#ifdef	DEBUG
	PCT.6 ^= 1;						/* LED1ȿž	(Interface��Ͽ������)			*/
#endif
}
#endif
/*	---------------------------------------------------------------------------	*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
