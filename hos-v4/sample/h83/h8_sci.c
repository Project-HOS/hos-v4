/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   H8/3048�� SCI����饤�֥��                                            */
/*                                                                          */
/* 1. ����Ԥ��ܥ������ե���������Ѥˤ�ä�ȯ������ǡ���ʤ�»���ˤ⤽��    */
/*    ��Ǥ���餤�ޤ���                                                    */
/* 2. �����ۤˤ������������ڤ����ջ���ξ�������Ǥ��ؤ��ޤ���        */
/* 3. �嵭����¤ꡢ���Ǥ�����Τκ����ۤ�ޤᡢ���ѡ����Ѥ���鷺      */
/*    ���������Ӥ˼�ͳ�����ѤǤ��ޤ���                                    */
/* 4. ����ʪ�κ����ۻ��ϡ����ǼԤ���������Ϣ�����ɬ���ɵ����Ƥ���������  */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


/* �������Ǥϡ��ƥ����Ѥ˥ݡ���󥰤�ʸ����Ф��Τ� */


#include "h8_3048.h"
#include "h8_sci.h"



/* ���ѥݡ��Ȥ���� */
#ifdef __USE_SCI0
#define SMR     SMR0
#define BRR     BRR0
#define SCR     SCR0
#define TDR     TDR0
#define SSR     SSR0
#define RDR     RDR0
#else
#define SMR     SMR1
#define BRR     BRR1
#define SCR     SCR1
#define TDR     TDR1
#define SSR     SSR1
#define RDR     RDR1
#endif



/* SCI����� */
void SCI_Init(unsigned char rate)
{
	volatile int v;
	int i;
	
	/* SCI����� */
	SCR  = 0x00;
	SMR  = 0x00;
	BRR  = rate;
	for ( i = 0; i < 280; i++ )
		v++;
	SCR  = 0x50;
	SSR &= 0x80;
}


/* ��ʸ������ */
void SCI_Putc(char c)
{
	while ( !(SSR & 0x80) )
		;
	TDR  = c;
	SSR &= 0x7f;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
