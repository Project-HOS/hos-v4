/* ------------------------------------------------------------------------ */
/*  日立 SH7045 用ヘッダファイル                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
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

#define SH_SCR_TIE		0x80
#define SH_SCR_RIE		0x40
#define SH_SCR_TE		0x20
#define SH_SCR_RE		0x10
#define SH_SCR_MPIE		0x08
#define SH_SCR_TEIE		0x04
#define SH_SCR_CKE1		0x02
#define SH_SCR_CKE2		0x01

#define SH_SSR_TDRE		0x80
#define SH_SSR_TDRF		0x40
#define SH_SSR_ORER		0x20
#define SH_SSR_FER		0x10
#define SH_SSR_PER		0x08
#define SH_SSR_TEND		0x04
#define SH_SSR_MPB		0x02
#define SH_SSR_MPBT		0x01


/* コンペアマッチタイマ */
#define SH_CMSTR	((volatile unsigned short *)0xffff83d0)
#define SH_CMCSR0	((volatile unsigned short *)0xffff83d2)
#define SH_CMCNT0	((volatile unsigned short *)0xffff83d4)
#define SH_CMCOR0	((volatile unsigned short *)0xffff83d6)
#define SH_CMCSR1	((volatile unsigned short *)0xffff83d8)
#define SH_CMCNT1	((volatile unsigned short *)0xffff83da)
#define SH_CMCOR1	((volatile unsigned short *)0xffff83dc)


/* 割り込み番号定義 */
#define SH_INTNUM_NMI			11
#define SH_INTNUM_USRBRK		12
#define SH_INTNUM_IRQ0			64
#define SH_INTNUM_IRQ1			65
#define SH_INTNUM_IRQ2			66
#define SH_INTNUM_IRQ3			67
#define SH_INTNUM_IRQ4			68
#define SH_INTNUM_IRQ5			69
#define SH_INTNUM_IRQ6			70
#define SH_INTNUM_IRQ7			71
#define SH_INTNUM_DEI0			72
#define SH_INTNUM_DEI1			76
#define SH_INTNUM_DEI2			80
#define SH_INTNUM_DEI3			84
#define SH_INTNUM_TGI0A			88
#define SH_INTNUM_TGI0B			89
#define SH_INTNUM_TGI0C			90
#define SH_INTNUM_TGI0D			91
#define SH_INTNUM_TGI0U			92
#define SH_INTNUM_TGI1A			96
#define SH_INTNUM_TGI1B			97
#define SH_INTNUM_TGI1V			100
#define SH_INTNUM_TGI1U			101
#define SH_INTNUM_TGI2A			104
#define SH_INTNUM_TGI2B			105
#define SH_INTNUM_TGI2V			108
#define SH_INTNUM_TGI2U			109
#define SH_INTNUM_TGI3A			112
#define SH_INTNUM_TGI3B			113
#define SH_INTNUM_TGI3C			114
#define SH_INTNUM_TGI3D			115
#define SH_INTNUM_TGI3V			116
#define SH_INTNUM_TGI4A			120
#define SH_INTNUM_TGI4B			121
#define SH_INTNUM_TGI4C			122
#define SH_INTNUM_TGI4D			123
#define SH_INTNUM_TGI4V			124
#define SH_INTNUM_ERI0			128
#define SH_INTNUM_RXI0			129
#define SH_INTNUM_TXI0			130
#define SH_INTNUM_TEI0			131
#define SH_INTNUM_ERI1			132
#define SH_INTNUM_RXI1			133
#define SH_INTNUM_TXI1			134
#define SH_INTNUM_TEI1			135
#define SH_INTNUM_ADI0			136
#define SH_INTNUM_ADI1			137
#define SH_INTNUM_SWDTCE		140
#define SH_INTNUM_CMI0			144
#define SH_INTNUM_CMI1			148
#define SH_INTNUM_ITI			152
#define SH_INTNUM_CMI			153
#define SH_INTNUM_OEI			156


#endif	/* __sh7045_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
