/* ------------------------------------------------------------------------ */
/*  日立 SH7045 用ヘッダファイル                                            */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __sh7045_h__
#define __sh7045_h__


/* ビットフィールドを使うのは便利なんですが、コンパイラ依存に */
/* なるので止めときます (^^;;                                 */

/* 割り込みコントローラー */
#define SH_IPRA		((volatile unsigned short *)0xffff8348)
#define SH_IPRB		((volatile unsigned short *)0xffff834a)
#define SH_IPRC		((volatile unsigned short *)0xffff834c)
#define SH_IPRD		((volatile unsigned short *)0xffff834e)
#define SH_IPRE		((volatile unsigned short *)0xffff8350)
#define SH_IPRF		((volatile unsigned short *)0xffff8352)
#define SH_IPRG		((volatile unsigned short *)0xffff8354)
#define SH_IPRH		((volatile unsigned short *)0xffff8356)
#define SH_ICR		((volatile unsigned short *)0xffff8358)
#define SH_ISR		((volatile unsigned short *)0xffff835a)


/* ピンファンクションコントロール */
#define SH_PAIORH	((volatile unsigned short *)0xffff8384)
#define SH_PAIOL	((volatile unsigned short *)0xffff8386)
#define SH_PACRH	((volatile unsigned short *)0xffff8388)
#define SH_PACRL1	((volatile unsigned short *)0xffff838c)
#define SH_PACRL2	((volatile unsigned short *)0xffff838e)
#define SH_PBIOR	((volatile unsigned short *)0xffff8394)
#define SH_PBCR1	((volatile unsigned short *)0xffff8398)
#define SH_PBCR2	((volatile unsigned short *)0xffff839a)
#define SH_PCIOR	((volatile unsigned short *)0xffff8396)
#define SH_PCCR		((volatile unsigned short *)0xffff839c)
#define SH_PDIORH	((volatile unsigned short *)0xffff83a4)
#define SH_PDIORL	((volatile unsigned short *)0xffff83a6)
#define SH_PDCRH1	((volatile unsigned short *)0xffff83a8)
#define SH_PDCRH2	((volatile unsigned short *)0xffff83aa)
#define SH_PDCRL	((volatile unsigned short *)0xffff83ac)
#define SH_PEIOR	((volatile unsigned short *)0xffff83b4)
#define SH_PECR1	((volatile unsigned short *)0xffff83b8)
#define SH_PECR2	((volatile unsigned short *)0xffff83ba)
#define SH_IFCR		((volatile unsigned short *)0xffff83c8)

#define SH_PEDR		((volatile unsigned short *)0xffff83b0)


/* シリアルコミュニケーションインターフェース */
#define SH_SMR0		((volatile unsigned char *)0xffff81a0)
#define SH_BRR0		((volatile unsigned char *)0xffff81a1)
#define SH_SCR0		((volatile unsigned char *)0xffff81a2)
#define SH_TDR0		((volatile unsigned char *)0xffff81a3)
#define SH_SSR0		((volatile unsigned char *)0xffff81a4)
#define SH_RDR0		((volatile unsigned char *)0xffff81a5)
#define SH_SMR1		((volatile unsigned char *)0xffff81b0)
#define SH_BRR1		((volatile unsigned char *)0xffff81b1)
#define SH_SCR1		((volatile unsigned char *)0xffff81b2)
#define SH_TDR1		((volatile unsigned char *)0xffff81b3)
#define SH_SSR1		((volatile unsigned char *)0xffff81b4)
#define SH_RDR1		((volatile unsigned char *)0xffff81b5)


/* コンペアマッチタイマ */
#define SH_CMSTR	((volatile unsigned short *)0xffff83d0)
#define SH_CMCSR0	((volatile unsigned short *)0xffff83d2)
#define SH_CMCNT0	((volatile unsigned short *)0xffff83d4)
#define SH_CMCOR0	((volatile unsigned short *)0xffff83d6)
#define SH_CMCSR1	((volatile unsigned short *)0xffff83d8)
#define SH_CMCNT1	((volatile unsigned short *)0xffff83da)
#define SH_CMCOR1	((volatile unsigned short *)0xffff83dc)


#endif	/* __sh7045_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */
/* ------------------------------------------------------------------------ */
