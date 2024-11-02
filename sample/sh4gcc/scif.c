/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*  SH7750 SCIF制御(ポーリング出力のみ)                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include "kernel.h"
#include "sh7750.h"
#include "scif.h"

void scif_open( int bcode)
{
  volatile register int i;

  SCIF.SCSCR.WORD = 0; /* SCSCR2のTE=RE=0 */
  SCIF.SCSMR.WORD = 0; /* SCSMR2: 8bit none parity 1 stop bit 内部clock */

  /* 送受FIFO初期化 */
  SCIF.SCFCR.WORD = SCIF_SCFCR_TFRST | SCIF_SCFCR_RFRST;
  /* modem制御有 */
  SCIF.SCFCR.WORD = SCIF_SCFCR_MCE;

  SCIF.SCSPTR.WORD = 0; /* CTS/RTS */
  SCIF.SCLSR.WORD = 0; /* ORFERオーバーランフラグクリア */

  i = SCIF.SCFSR.WORD;
  SCIF.SCFSR.WORD = SCIF_SCFSR_TEND | SCIF_SCFSR_TDFE;
  i = SCIF.SCLSR.WORD;
  SCIF.SCLSR.WORD = 0;

  /* ビットレート設定 */
  SCIF.SCBRR = (unsigned char)bcode;

 /* いい加減な待ち */
  for ( i=0; i<bcode*160; i++);

 /* TE=RE=1:送受信可 TIE=RIE=REIE=0:通信割込禁止 */
  SCIF.SCSCR.WORD = SCIF_SCSCR_TE | SCIF_SCSCR_RE;
}

void scif_putc( int code)
{
  int i;

  /* TENDをクリア(1を読んでから0を書く) */
  while (!(( i = SCIF.SCFSR.WORD) & SCIF_SCFSR_TEND));
  SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;

  /* FIFOに空きが出来るまで待つ */
  while ( SCIF.SCFDR.WORD & 0x1000 );

  /* 一文字書き込む */
  SCIF.SCFTDR = (unsigned char)code;

  /* 一文字送信 */
  while ((( i = SCIF.SCFSR.WORD) & (SCIF_SCFSR_TEND|SCIF_SCFSR_TDFE)) != 
	  (SCIF_SCFSR_TEND|SCIF_SCFSR_TDFE));
  SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;

  /* FIFOが空,最後の一文字の送信完了を待つ */
//  while ( SCIF.SCFDR.WORD & 0x1f00);
//  while (!(SCIF.SCFSR.WORD & SCIF_SCFSR_TEND));
}

void scif_init( VP_INT exf){}

void scif_puts( char  *p)
{
  int  i;

  do {
    /* FIFOに空きが出来るまで待つ */
    while ( (i = (SCIF.SCFDR.WORD & 0x1f00)>>8) == 16 );
    /* FIFOの空きの分だけ書き込む */
    for ( i = 16-i; i>0 && *p ; i--)
      SCIF.SCFTDR = *p++;
    while (!(( i = SCIF.SCFSR.WORD) & SCIF_SCFSR_TEND));
    SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;
  } while ( *p);

  /* FIFOが空,最後の一文字の送信完了を待つ */
//  while ( SCIF.SCFDR.WORD & 0x1f00);
//  while (!(SCIF.SCFSR.WORD & SCIF_SCFSR_TEND));
}

void scif_snd_hdr( VP_INT exinf){}
void scif_rcv_hdr( VP_INT exinf){}
int scif_getc(void){return 0;}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
