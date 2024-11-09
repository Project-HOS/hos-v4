/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*  SH7750 INTC初期化,割り込みマスクテーブル                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include <stdio.h>
#include "kernel.h"
#include "sh7750.h"
#include "scif.h"

/* 割り込み番号に対する優先順位のテーブル int_pri_tble[] */
/* 割り込み番号 = (例外コード >> 5) - 16
   優先順位     = 0 〜 15 (数字の大きい方が優先される) 
   但し,モジール毎の優先順位は同じであること
     例: SCI (ERI) = SCI (RXI) = SCI (TXI) = SCI (TEI) */
B int_pri_tbl[] = {
	/* IRLの優先順位は固定 */
	/*        名称                 例外コード  割り込み番号 */
	15,    /* IRL3210 =  0         0x200       00 */
	14,    /* IRL3210 =  1         0x220       01 */
	13,    /* IRL3210 =  2 (IRL 0) 0x240       02 */
	12,    /* IRL3210 =  3         0x260       03 */
	11,    /* IRL3210 =  4         0x280       04 */
	10,    /* IRL3210 =  5 (IRL 1) 0x2a0       05 */
	9,     /* IRL3210 =  6         0x2c0       06 */
	8,     /* IRL3210 =  7         0x2e0       07 */

	7,     /* IRL3210 =  8 (IRL 2) 0x300       08 */
	6,     /* IRL3210 =  9         0x320       09 */
	5,     /* IRL3210 =  A         0x340       10 */
	4,     /* IRL3210 =  B (IRL 3) 0x360       11 */
	3,     /* IRL3210 =  C         0x380       12 */
	2,     /* IRL3210 =  D         0x3a0       13 */
	1,     /* IRL3210 =  E         0x3c0       14 */
	-1,    /* --                   0x3e0       15 */

	/* 内蔵モジュールはここで設定可能 */
	15,    /* TMU0 TUNI0           0x400       16 */ /* システムタイマ */
	0,     /* TMU1 TUNI1           0x420       17 */
	0,     /* TMU2 (TUNI2)         0x440       18 */
	0,     /* TMU2 (TICPI2)        0x460       19 */
	0,     /* RTC (ATI)            0x480       20 */
	0,     /* RTC (PRI)            0x4a0       21 */
	0,     /* RTC (CUI)            0x4c0       22 */
	0,     /* SCI (ERI)            0x4e0       23 */

	0,     /* SCI (RXI)            0x500       24 */
	0,     /* SCI (TXI)            0x520       25 */
	0,     /* SCI (TEI)            0x540       26 */
	0,     /* WDT ITI              0x560       27 */
	0,     /* REF (RCMI)           0x580       28 */
	0,     /* REF (ROVI)           0x5a0       29 */
	-1,    /* --                   0x5c0       30 */
	-1,    /* --                   0x5e0       31 */

	0,     /* Hitachi-UDI          0x600       32 */
	0,     /* GPIO                 0x620       33 */
	0,     /* DMAC  (DMTE0)        0x640       34 */
	0,     /* DMAC  (DMTE1)        0x660       35 */
	0,     /* DMAC  (DMTE2)        0x680       36 */
	0,     /* DMAC  (DMTE3)        0x6a0       37 */
	0,     /* DMAC  (DMAE)         0x6c0       38 */
	-1,    /* --                   0x6e0       39 */

	10,     /* SCIF  (ERI)          0x700       40 */
	10,     /* SCIF  (RXI)          0x720       41 */
	10,     /* SCIF  (BRI)          0x740       42 */
	10      /* SCIF  (TXI)          0x760       43 */
};

/* INTCの初期化 */
void intc_int(void)
{
	/* ここで割り込みコントローラーを初期化 */

	/* 内蔵ペリフェラルの優先順位を設定 */
	INTC.IPRA.WORD = /* TMU0 TMU1 TMU2 RTC */
		(( int_pri_tbl[SH4_INTNUM_TMU0_TUNI0] << 12 ) |
		 ( int_pri_tbl[SH4_INTNUM_TMU1_TUNI1] <<  8 ) |
		 ( int_pri_tbl[SH4_INTNUM_TMU2_TUNI2] <<  4 ) |
		 ( int_pri_tbl[SH4_INTNUM_RTC_ATI] )); 

	INTC.IPRB.WORD = /* WDT REF SCI 0 */
		(( int_pri_tbl[SH4_INTNUM_WDT_ITI]  << 12 ) |
		 ( int_pri_tbl[SH4_INTNUM_REF_RCMI] <<  8 ) |
		 ( int_pri_tbl[SH4_INTNUM_SCI_ERI]  <<  4 ));

	INTC.IPRC.WORD = /* GPIO DMAC SCIF UDI */
		(( int_pri_tbl[SH4_INTNUM_GPIO]       << 12 ) |
		 ( int_pri_tbl[SH4_INTNUM_DMAC_DMTE0] <<  8 ) |
		 ( int_pri_tbl[SH4_INTNUM_SCIF_ERI]   <<  4 ) |
		 ( int_pri_tbl[SH4_INTNUM_UDI] )); 
}

void ItoA( int num, char *str)
{
	int i;
	char *p = str+9;

	*p = '\0';
	while ( str <= p ) {
		i = num & 0xf;
		*p-- = i < 10 ?  '0'+i: 'A'+i-10;
		num >>= 4;
	}
}

void exception_hdr( UINT expevt, UINT spc, UINT ssr)
{
	char str[9];

	scif_puts("expevt = 0x");
	ItoA( expevt, str);
	scif_puts(str);

	scif_puts(" spc = 0x");
	ItoA( spc, str);
	scif_puts(str);

	scif_puts(" ssr = 0x");
	ItoA( ssr, str);
	scif_puts(str);

	scif_putc('\n');

	for(;;);
}


int __read (char *ptr, int len)
{
	int i;

	for ( i=0; i<len; i++)  ptr[i] = scif_getc();

	return len;
}

int __write ( char *ptr, int len)
{
	int i;

	for ( i=0; i<len; i++) scif_putc( ptr[i]);

	return len;
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
