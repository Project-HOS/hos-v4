/* ------------------------------------------------------------------------ */
/*  H8/3664�� SCI3����饤�֥��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "h83664f.h"
#include "h8t_sci.h"

/* SCI3����� */
void SCI3_Initialize(unsigned char rate)
{
	volatile int i;
	
	/* SCI3����� */
	SCI3.SCR3.BYTE = 0x00;
	SCI3.SMR.BYTE = 0x00;
	SCI3.BRR = rate;
	for ( i = 0; i < 280; i++ )
		;
	SCI3.SCR3.BYTE = 0x20; /* ������ */
	IO.PMR1.BIT.TXD = 1;
}

/* ��ʸ������ */
void SCI3_PutChar(char c)
{
	while ( !(SCI3.SSR.BYTE & 0x80) )
		;

	SCI3.TDR  = c;
/*      SCI3.SSR.BYTE &= 0x7f;  */
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
