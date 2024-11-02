/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*  SH7750 INTC初期化,割り込みマスクテーブル                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __PROJECT_HOS__sh7750_h__
#define __PROJECT_HOS__sh7750_h__

/* 手抜きです。*.BIT.* さえ使わなければ問題無し！ */
#include <7750S.H> 
/* /usr/local/include/hitachi/SH4/ に叩き込んであります */

/* 割り込み番号定義 */
#define SH4_INTNUM_IRL0		0
#define SH4_INTNUM_IRL1		1
#define SH4_INTNUM_IRL2		2
#define SH4_INTNUM_IRL3		3
#define SH4_INTNUM_IRL4		4
#define SH4_INTNUM_IRL5		5
#define SH4_INTNUM_IRL6		6
#define SH4_INTNUM_IRL7		7
#define SH4_INTNUM_IRL8		8
#define SH4_INTNUM_IRL9		9
#define SH4_INTNUM_IRL10	10
#define SH4_INTNUM_IRL11	11
#define SH4_INTNUM_IRL12	12
#define SH4_INTNUM_IRL13	13
#define SH4_INTNUM_IRL14	14

#define SH4_INTNUM_TMU0_TUNI0	16
#define SH4_INTNUM_TMU1_TUNI1	17
#define SH4_INTNUM_TMU2_TUNI2	18
#define SH4_INTNUM_TMU2_TICPI2	19
#define SH4_INTNUM_RTC_ATI	20
#define SH4_INTNUM_RTC_PRI	21
#define SH4_INTNUM_RTC_CUI	22
#define SH4_INTNUM_SCI_ERI	23
#define SH4_INTNUM_SCI_RXI	24
#define SH4_INTNUM_SCI_TXI	25
#define SH4_INTNUM_SCI_TEI	26
#define SH4_INTNUM_WDT_ITI	27
#define SH4_INTNUM_REF_RCMI	28
#define SH4_INTNUM_REF_ROVI	29

#define SH4_INTNUM_UDI		32
#define SH4_INTNUM_GPIO		33
#define SH4_INTNUM_DMAC_DMTE0	34
#define SH4_INTNUM_DMAC_DMTE1	35
#define SH4_INTNUM_DMAC_DMTE2	36
#define SH4_INTNUM_DMAC_DMTE3	37
#define SH4_INTNUM_DMAC_DMAE	38

#define SH4_INTNUM_SCIF_ERI	40
#define SH4_INTNUM_SCIF_RXI	41
#define SH4_INTNUM_SCIF_BRI	42
#define SH4_INTNUM_SCIF_TXI	43

/* SCIF */
#define SCIF_SCSCR_TIE	0x0080
#define SCIF_SCSCR_RIE	0x0040
#define SCIF_SCSCR_TE	0x0020
#define SCIF_SCSCR_RE	0x0010
#define SCIF_SCSCR_REIE	0x0008
#define SCIF_SCSCR_CKE	0x0020

#define SCIF_SCFSR_ER	0x0080
#define SCIF_SCFSR_TEND	0x0040
#define SCIF_SCFSR_TDFE	0x0020
#define SCIF_SCFSR_BRK	0x0010
#define SCIF_SCFSR_FER	0x0008
#define SCIF_SCFSR_PER	0x0004
#define SCIF_SCFSR_RDF	0x0002
#define SCIF_SCFSR_DR	0x0001

#define SCIF_SCFCR_MCE		0x0008
#define SCIF_SCFCR_TFRST	0x0004
#define SCIF_SCFCR_RFRST	0x0002
#define SCIF_SCFCR_LOOP		0x0001

/* sh7750.c 内のプロトタイプ */
#ifdef __cplusplus
extern "C" {
#endif

void intc_int(void);
void exception_hdr( UINT, UINT, UINT);
int __read (char *, int);
int __write ( char *, int);

#ifdef __cplusplus
}
#endif

#endif	/* __PROJECT_HOS__sh7750_h__ */

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
