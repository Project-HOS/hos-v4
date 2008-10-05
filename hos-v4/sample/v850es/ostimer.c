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
/*	---------------------------------------------------------------------------	*/
/*										Copyright (C) 1998-2008 by Project HOS	*/
/*										http://sourceforge.jp/projects/hos/		*/
/*	---------------------------------------------------------------------------	*/
