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
#define ABWCR   (*((unsigned char *)0xffffec))
#define ASTCR   (*((unsigned char *)0xffffed))
#define WCR     (*((unsigned char *)0xffffee))
#define WCER    (*((unsigned char *)0xffffef))
#define BRCR    (*((unsigned char *)0xfffff3))
#define CSCR    (*((unsigned char *)0xffff5f))


/* IOポート */
#define P1DDR   (*((unsigned char *)0xffffc0))
#define P1DR    (*((unsigned char *)0xffffc2))

#define P2DDR   (*((unsigned char *)0xffffc1))
#define P2DR    (*((unsigned char *)0xffffc3))
#define P2PCR   (*((unsigned char *)0xffffd8))

#define P3DDR   (*((unsigned char *)0xffffc4))
#define P3DR    (*((unsigned char *)0xffffc6))

#define P4DDR   (*((unsigned char *)0xffffc5))
#define P4DR    (*((unsigned char *)0xffffc7))
#define P4PCR   (*((unsigned char *)0xffffda))

#define P5DDR   (*((unsigned char *)0xffffc8))
#define P5DR    (*((unsigned char *)0xffffca))
#define P5PCR   (*((unsigned char *)0xffffdb))

#define P6DDR   (*((unsigned char *)0xffffc9))
#define P6DR    (*((unsigned char *)0xffffcb))

#define P7DR    (*((unsigned char *)0xffffce))

#define P8DDR   (*((unsigned char *)0xffffcd))
#define P8DR    (*((unsigned char *)0xffffcf))

#define P9DDR   (*((unsigned char *)0xffffd0))
#define P9DR    (*((unsigned char *)0xffffd2))

#define PADDR   (*((unsigned char *)0xffffd1))
#define PADR    (*((unsigned char *)0xffffd3))

#define PBDDR   (*((unsigned char *)0xffffd4))
#define PBDR    (*((unsigned char *)0xffffd6))


/* ITU */
#define TSTR    (*((unsigned char *)(0xffff60)))
#define TSNC    (*((unsigned char *)(0xffff61)))
#define TMDR    (*((unsigned char *)(0xffff62)))
#define TFCR    (*((unsigned char *)(0xffff63)))
#define TOER    (*((unsigned char *)(0xffff90)))
#define TOCR    (*((unsigned char *)(0xffff91)))

#define TCR0    (*((unsigned char *)(0xffff64)))
#define TIOR0   (*((unsigned char *)(0xffff65)))
#define TIER0   (*((unsigned char *)(0xffff66)))
#define TSR0    (*((unsigned char *)(0xffff67)))
#define TCNT0   (*((unsigned int  *)(0xffff68)))
#define TCNT0H  (*((unsigned char *)(0xffff68)))
#define TCNT0L  (*((unsigned char *)(0xffff69)))
#define GRA0    (*((unsigned int  *)(0xffff6a)))
#define GRA0H   (*((unsigned char *)(0xffff6a)))
#define GRA0L   (*((unsigned char *)(0xffff6b)))
#define GRB0    (*((unsigned int  *)(0xffff6c)))
#define GRB0H   (*((unsigned char *)(0xffff6c)))
#define GRB0L   (*((unsigned char *)(0xffff6d)))

#define TCR1    (*((unsigned char *)(0xffff6e)))
#define TIOR1   (*((unsigned char *)(0xffff6f)))
#define TIER1   (*((unsigned char *)(0xffff70)))
#define TSR1    (*((unsigned char *)(0xffff71)))
#define TCNT1   (*((unsigned int  *)(0xffff72)))
#define TCNT1H  (*((unsigned char *)(0xffff72)))
#define TCNT1L  (*((unsigned char *)(0xffff73)))
#define GRA1    (*((unsigned int  *)(0xffff74)))
#define GRA1H   (*((unsigned char *)(0xffff74)))
#define GRA1L   (*((unsigned char *)(0xffff75)))
#define GRB1    (*((unsigned int  *)(0xffff76)))
#define GRB1H   (*((unsigned char *)(0xffff76)))
#define GRB1L   (*((unsigned char *)(0xffff77)))

#define TCR2    (*((unsigned char *)(0xffff78)))
#define TIOR2   (*((unsigned char *)(0xffff79)))
#define TIER2   (*((unsigned char *)(0xffff7a)))
#define TSR2    (*((unsigned char *)(0xffff7b)))
#define TCNT2   (*((unsigned int  *)(0xffff7c)))
#define TCNT2H  (*((unsigned char *)(0xffff7c)))
#define TCNT2L  (*((unsigned char *)(0xffff7d)))
#define GRA2    (*((unsigned int  *)(0xffff7e)))
#define GRA2H   (*((unsigned char *)(0xffff7e)))
#define GRA2L   (*((unsigned char *)(0xffff7f)))
#define GRB2    (*((unsigned int  *)(0xffff80)))
#define GRB2H   (*((unsigned char *)(0xffff80)))
#define GRB2L   (*((unsigned char *)(0xffff81)))

#define TCR3    (*((unsigned char *)(0xffff82)))
#define TIOR3   (*((unsigned char *)(0xffff83)))
#define TIER3   (*((unsigned char *)(0xffff84)))
#define TSR3    (*((unsigned char *)(0xffff85)))
#define TCNT3   (*((unsigned int  *)(0xffff86)))
#define TCNT3H  (*((unsigned char *)(0xffff86)))
#define TCNT3L  (*((unsigned char *)(0xffff87)))
#define GRA3    (*((unsigned int  *)(0xffff88)))
#define GRA3H   (*((unsigned char *)(0xffff88)))
#define GRA3L   (*((unsigned char *)(0xffff89)))
#define GRB3    (*((unsigned int  *)(0xffff8a)))
#define GRB3H   (*((unsigned char *)(0xffff8a)))
#define GRB3L   (*((unsigned char *)(0xffff8b)))
#define BRA3    (*((unsigned int  *)(0xffff8c)))
#define BRA3H   (*((unsigned char *)(0xffff8c)))
#define BRA3L   (*((unsigned char *)(0xffff8d)))
#define BRB3    (*((unsigned int  *)(0xffff8e)))
#define BRB3H   (*((unsigned char *)(0xffff8e)))
#define BRB3L   (*((unsigned char *)(0xffff8f)))

#define TCR4    (*((unsigned char *)(0xffff92)))
#define TIOR4   (*((unsigned char *)(0xffff93)))
#define TIER4   (*((unsigned char *)(0xffff94)))
#define TSR4    (*((unsigned char *)(0xffff95)))
#define TCNT4   (*((unsigned int  *)(0xffff96)))
#define TCNT4H  (*((unsigned char *)(0xffff96)))
#define TCNT4L  (*((unsigned char *)(0xffff97)))
#define GRA4    (*((unsigned int  *)(0xffff98)))
#define GRA4H   (*((unsigned char *)(0xffff98)))
#define GRA4L   (*((unsigned char *)(0xffff99)))
#define GRB4    (*((unsigned int  *)(0xffff9a)))
#define GRB4H   (*((unsigned char *)(0xffff9a)))
#define GRB4L   (*((unsigned char *)(0xffff9b)))
#define BRA4    (*((unsigned int  *)(0xffff9c)))
#define BRA4H   (*((unsigned char *)(0xffff9c)))
#define BRA4L   (*((unsigned char *)(0xffff9d)))
#define BRB4    (*((unsigned int  *)(0xffff9e)))
#define BRB4H   (*((unsigned char *)(0xffff9e)))
#define BRB4L   (*((unsigned char *)(0xffff9f)))


/* DAコンバーター */
#define DADR0   (*((unsigned char *)(0xffffdc)))
#define DADR1   (*((unsigned char *)(0xffffdd)))
#define DACR    (*((unsigned char *)(0xffffde)))
#define DASTCR  (*((unsigned char *)(0xffff5c)))


/* シリアルコミュニケーションインターフェース */
#define SMR0    (*((unsigned char *)(0xffffb0)))
#define BRR0    (*((unsigned char *)(0xffffb1)))
#define SCR0    (*((unsigned char *)(0xffffb2)))
#define TDR0    (*((unsigned char *)(0xffffb3)))
#define SSR0    (*((unsigned char *)(0xffffb4)))
#define RDR0    (*((unsigned char *)(0xffffb5)))

#define SMR1    (*((unsigned char *)(0xffffb8)))
#define BRR1    (*((unsigned char *)(0xffffb9)))
#define SCR1    (*((unsigned char *)(0xffffba)))
#define TDR1    (*((unsigned char *)(0xffffbb)))
#define SSR1    (*((unsigned char *)(0xffffbc)))
#define RDR1    (*((unsigned char *)(0xffffbd)))


/* ADコンバーター */
#define ADDRA   (*((unsigned int  *)(0xffffe0)))
#define ADDRAH  (*((unsigned char *)(0xffffe0)))
#define ADDRAL  (*((unsigned char *)(0xffffe1)))
#define ADDRB   (*((unsigned int  *)(0xffffe2)))
#define ADDRBH  (*((unsigned char *)(0xffffe2)))
#define ADDRBL  (*((unsigned char *)(0xffffe3)))
#define ADDRC   (*((unsigned int  *)(0xffffe4)))
#define ADDRCH  (*((unsigned char *)(0xffffe4)))
#define ADDRCL  (*((unsigned char *)(0xffffe5)))
#define ADDRD   (*((unsigned int  *)(0xffffe6)))
#define ADDRDH  (*((unsigned char *)(0xffffe6)))
#define ADDRDL  (*((unsigned char *)(0xffffe7)))
#define ADCSR   (*((unsigned char *)(0xffffe8)))
#define ADCR    (*((unsigned char *)(0xffffe9)))



#endif	/* __PROJECT_HOS__h8_3048_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
