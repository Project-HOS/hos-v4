/* ------------------------------------------------------------------------ */
/*  H8/3048 用 ヘッダファイル                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


/* 今のところ超適当に使ってる奴だけ定義 (^^; */


#ifndef __PROJECT_HOS__h8_3048_h__
#define __PROJECT_HOS__h8_3048_h__



/* バスコントローラー */
#define ABWCR   (*((volatile unsigned char *)0xffffec))
#define ASTCR   (*((volatile unsigned char *)0xffffed))
#define WCR     (*((volatile unsigned char *)0xffffee))
#define WCER    (*((volatile unsigned char *)0xffffef))
#define BRCR    (*((volatile unsigned char *)0xfffff3))
#define CSCR    (*((volatile unsigned char *)0xffff5f))


/* IOポート */
#define P1DDR   (*((volatile unsigned char *)0xffffc0))
#define P1DR    (*((volatile unsigned char *)0xffffc2))

#define P2DDR   (*((volatile unsigned char *)0xffffc1))
#define P2DR    (*((volatile unsigned char *)0xffffc3))
#define P2PCR   (*((volatile unsigned char *)0xffffd8))

#define P3DDR   (*((volatile unsigned char *)0xffffc4))
#define P3DR    (*((volatile unsigned char *)0xffffc6))

#define P4DDR   (*((volatile unsigned char *)0xffffc5))
#define P4DR    (*((volatile unsigned char *)0xffffc7))
#define P4PCR   (*((volatile unsigned char *)0xffffda))

#define P5DDR   (*((volatile unsigned char *)0xffffc8))
#define P5DR    (*((volatile unsigned char *)0xffffca))
#define P5PCR   (*((volatile unsigned char *)0xffffdb))

#define P6DDR   (*((volatile unsigned char *)0xffffc9))
#define P6DR    (*((volatile unsigned char *)0xffffcb))

#define P7DR    (*((volatile unsigned char *)0xffffce))

#define P8DDR   (*((volatile unsigned char *)0xffffcd))
#define P8DR    (*((volatile unsigned char *)0xffffcf))

#define P9DDR   (*((volatile unsigned char *)0xffffd0))
#define P9DR    (*((volatile unsigned char *)0xffffd2))

#define PADDR   (*((volatile unsigned char *)0xffffd1))
#define PADR    (*((volatile unsigned char *)0xffffd3))

#define PBDDR   (*((volatile unsigned char *)0xffffd4))
#define PBDR    (*((volatile unsigned char *)0xffffd6))


/* ITU */
#define TSTR    (*((volatile unsigned char *)(0xffff60)))
#define TSNC    (*((volatile unsigned char *)(0xffff61)))
#define TMDR    (*((volatile unsigned char *)(0xffff62)))
#define TFCR    (*((volatile unsigned char *)(0xffff63)))
#define TOER    (*((volatile unsigned char *)(0xffff90)))
#define TOCR    (*((volatile unsigned char *)(0xffff91)))

#define TCR0    (*((volatile unsigned char *)(0xffff64)))
#define TIOR0   (*((volatile unsigned char *)(0xffff65)))
#define TIER0   (*((volatile unsigned char *)(0xffff66)))
#define TSR0    (*((volatile unsigned char *)(0xffff67)))
#define TCNT0   (*((volatile unsigned int  *)(0xffff68)))
#define TCNT0H  (*((volatile unsigned char *)(0xffff68)))
#define TCNT0L  (*((volatile unsigned char *)(0xffff69)))
#define GRA0    (*((volatile unsigned int  *)(0xffff6a)))
#define GRA0H   (*((volatile unsigned char *)(0xffff6a)))
#define GRA0L   (*((volatile unsigned char *)(0xffff6b)))
#define GRB0    (*((volatile unsigned int  *)(0xffff6c)))
#define GRB0H   (*((volatile unsigned char *)(0xffff6c)))
#define GRB0L   (*((volatile unsigned char *)(0xffff6d)))

#define TCR1    (*((volatile unsigned char *)(0xffff6e)))
#define TIOR1   (*((volatile unsigned char *)(0xffff6f)))
#define TIER1   (*((volatile unsigned char *)(0xffff70)))
#define TSR1    (*((volatile unsigned char *)(0xffff71)))
#define TCNT1   (*((volatile unsigned int  *)(0xffff72)))
#define TCNT1H  (*((volatile unsigned char *)(0xffff72)))
#define TCNT1L  (*((volatile unsigned char *)(0xffff73)))
#define GRA1    (*((volatile unsigned int  *)(0xffff74)))
#define GRA1H   (*((volatile unsigned char *)(0xffff74)))
#define GRA1L   (*((volatile unsigned char *)(0xffff75)))
#define GRB1    (*((volatile unsigned int  *)(0xffff76)))
#define GRB1H   (*((volatile unsigned char *)(0xffff76)))
#define GRB1L   (*((volatile unsigned char *)(0xffff77)))

#define TCR2    (*((volatile unsigned char *)(0xffff78)))
#define TIOR2   (*((volatile unsigned char *)(0xffff79)))
#define TIER2   (*((volatile unsigned char *)(0xffff7a)))
#define TSR2    (*((volatile unsigned char *)(0xffff7b)))
#define TCNT2   (*((volatile unsigned int  *)(0xffff7c)))
#define TCNT2H  (*((volatile unsigned char *)(0xffff7c)))
#define TCNT2L  (*((volatile unsigned char *)(0xffff7d)))
#define GRA2    (*((volatile unsigned int  *)(0xffff7e)))
#define GRA2H   (*((volatile unsigned char *)(0xffff7e)))
#define GRA2L   (*((volatile unsigned char *)(0xffff7f)))
#define GRB2    (*((volatile unsigned int  *)(0xffff80)))
#define GRB2H   (*((volatile unsigned char *)(0xffff80)))
#define GRB2L   (*((volatile unsigned char *)(0xffff81)))

#define TCR3    (*((volatile unsigned char *)(0xffff82)))
#define TIOR3   (*((volatile unsigned char *)(0xffff83)))
#define TIER3   (*((volatile unsigned char *)(0xffff84)))
#define TSR3    (*((volatile unsigned char *)(0xffff85)))
#define TCNT3   (*((volatile unsigned int  *)(0xffff86)))
#define TCNT3H  (*((volatile unsigned char *)(0xffff86)))
#define TCNT3L  (*((volatile unsigned char *)(0xffff87)))
#define GRA3    (*((volatile unsigned int  *)(0xffff88)))
#define GRA3H   (*((volatile unsigned char *)(0xffff88)))
#define GRA3L   (*((volatile unsigned char *)(0xffff89)))
#define GRB3    (*((volatile unsigned int  *)(0xffff8a)))
#define GRB3H   (*((volatile unsigned char *)(0xffff8a)))
#define GRB3L   (*((volatile unsigned char *)(0xffff8b)))
#define BRA3    (*((volatile unsigned int  *)(0xffff8c)))
#define BRA3H   (*((volatile unsigned char *)(0xffff8c)))
#define BRA3L   (*((volatile unsigned char *)(0xffff8d)))
#define BRB3    (*((volatile unsigned int  *)(0xffff8e)))
#define BRB3H   (*((volatile unsigned char *)(0xffff8e)))
#define BRB3L   (*((volatile unsigned char *)(0xffff8f)))

#define TCR4    (*((volatile unsigned char *)(0xffff92)))
#define TIOR4   (*((volatile unsigned char *)(0xffff93)))
#define TIER4   (*((volatile unsigned char *)(0xffff94)))
#define TSR4    (*((volatile unsigned char *)(0xffff95)))
#define TCNT4   (*((volatile unsigned int  *)(0xffff96)))
#define TCNT4H  (*((volatile unsigned char *)(0xffff96)))
#define TCNT4L  (*((volatile unsigned char *)(0xffff97)))
#define GRA4    (*((volatile unsigned int  *)(0xffff98)))
#define GRA4H   (*((volatile unsigned char *)(0xffff98)))
#define GRA4L   (*((volatile unsigned char *)(0xffff99)))
#define GRB4    (*((volatile unsigned int  *)(0xffff9a)))
#define GRB4H   (*((volatile unsigned char *)(0xffff9a)))
#define GRB4L   (*((volatile unsigned char *)(0xffff9b)))
#define BRA4    (*((volatile unsigned int  *)(0xffff9c)))
#define BRA4H   (*((volatile unsigned char *)(0xffff9c)))
#define BRA4L   (*((volatile unsigned char *)(0xffff9d)))
#define BRB4    (*((volatile unsigned int  *)(0xffff9e)))
#define BRB4H   (*((volatile unsigned char *)(0xffff9e)))
#define BRB4L   (*((volatile unsigned char *)(0xffff9f)))


/* DAコンバーター */
#define DADR0   (*((volatile unsigned char *)(0xffffdc)))
#define DADR1   (*((volatile unsigned char *)(0xffffdd)))
#define DACR    (*((volatile unsigned char *)(0xffffde)))
#define DASTCR  (*((volatile unsigned char *)(0xffff5c)))


/* シリアルコミュニケーションインターフェース */
#define SMR0    (*((volatile unsigned char *)(0xffffb0)))
#define BRR0    (*((volatile unsigned char *)(0xffffb1)))
#define SCR0    (*((volatile unsigned char *)(0xffffb2)))
#define TDR0    (*((volatile unsigned char *)(0xffffb3)))
#define SSR0    (*((volatile unsigned char *)(0xffffb4)))
#define RDR0    (*((volatile unsigned char *)(0xffffb5)))

#define SMR1    (*((volatile unsigned char *)(0xffffb8)))
#define BRR1    (*((volatile unsigned char *)(0xffffb9)))
#define SCR1    (*((volatile unsigned char *)(0xffffba)))
#define TDR1    (*((volatile unsigned char *)(0xffffbb)))
#define SSR1    (*((volatile unsigned char *)(0xffffbc)))
#define RDR1    (*((volatile unsigned char *)(0xffffbd)))


/* ADコンバーター */
#define ADDRA   (*((volatile unsigned int  *)(0xffffe0)))
#define ADDRAH  (*((volatile unsigned char *)(0xffffe0)))
#define ADDRAL  (*((volatile unsigned char *)(0xffffe1)))
#define ADDRB   (*((volatile unsigned int  *)(0xffffe2)))
#define ADDRBH  (*((volatile unsigned char *)(0xffffe2)))
#define ADDRBL  (*((volatile unsigned char *)(0xffffe3)))
#define ADDRC   (*((volatile unsigned int  *)(0xffffe4)))
#define ADDRCH  (*((volatile unsigned char *)(0xffffe4)))
#define ADDRCL  (*((volatile unsigned char *)(0xffffe5)))
#define ADDRD   (*((volatile unsigned int  *)(0xffffe6)))
#define ADDRDH  (*((volatile unsigned char *)(0xffffe6)))
#define ADDRDL  (*((volatile unsigned char *)(0xffffe7)))
#define ADCSR   (*((volatile unsigned char *)(0xffffe8)))
#define ADCR    (*((volatile unsigned char *)(0xffffe9)))



#endif	/* __PROJECT_HOS__h8_3048_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
