/* ------------------------------------------------------------------------ */
/*  H8/3048�� SCI����饤�֥��                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
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

#define RECV_BUFSIZE	32		/* �����Хåե��Υ����� */



static unsigned char recv_buf[32];
static int head;
static int tail;



/* SCI����� */
void Sci_Initialize(unsigned char rate)
{
	volatile int v;
	int i;
	
	/* SCI����� */
	SCR  = 0x00;
	SMR  = 0x00;
	BRR  = rate;
	for ( i = 0; i < 280; i++ )
		v++;
	SCR  = 0x70;
	SSR &= 0x80;
	
	/* �����Хåե������ */
	head = 0;
	tail = 0;
}


/* ��ʸ������ */
void Sci_PutChar(char c)
{
	while ( !(SSR & 0x80) )
		;
	
	TDR  = c;
	SSR &= 0x7f;
}


/* ��ʸ������ */
int Sci_GetChar(void)
{
	if ( head == tail )
	{
		return -1;
	}
	
	return recv_buf[head++];
}


/* SCI���������� */
void Sci_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1ʸ������ */
	c = RDR;
	SSR &= 0xbf;
	
	/* �����������֤�׻� */
	next = tail + 1;
	if ( next >= RECV_BUFSIZE )
	{
		next = 0;
	}
	
	/* �����С��ե������å� */
	if ( next == head )
	{
		return;
	}
	
	/* �����Хåե��˳�Ǽ */
	recv_buf[tail] = c;
	tail = next;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
