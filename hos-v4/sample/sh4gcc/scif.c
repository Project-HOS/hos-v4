/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*  SH7750 SCIF����(�ݡ���󥰽��ϤΤ�)                                     */
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

  SCIF.SCSCR.WORD = 0; /* SCSCR2��TE=RE=0 */
  SCIF.SCSMR.WORD = 0; /* SCSMR2: 8bit none parity 1 stop bit ����clock */

  /* ����FIFO����� */
  SCIF.SCFCR.WORD = SCIF_SCFCR_TFRST | SCIF_SCFCR_RFRST;
  /* modem����ͭ */
  SCIF.SCFCR.WORD = SCIF_SCFCR_MCE;

  SCIF.SCSPTR.WORD = 0; /* CTS/RTS */
  SCIF.SCLSR.WORD = 0; /* ORFER�����С����ե饰���ꥢ */

  i = SCIF.SCFSR.WORD;
  SCIF.SCFSR.WORD = SCIF_SCFSR_TEND | SCIF_SCFSR_TDFE;
  i = SCIF.SCLSR.WORD;
  SCIF.SCLSR.WORD = 0;

  /* �ӥåȥ졼������ */
  SCIF.SCBRR = (unsigned char)bcode;

 /* �����ø����Ԥ� */
  for ( i=0; i<bcode*160; i++);

 /* TE=RE=1:�������� TIE=RIE=REIE=0:�̿�����ػ� */
  SCIF.SCSCR.WORD = SCIF_SCSCR_TE | SCIF_SCSCR_RE;
}

void scif_putc( int code)
{
  int i;

  /* TEND�򥯥ꥢ(1���ɤ�Ǥ���0���) */
  while (!(( i = SCIF.SCFSR.WORD) & SCIF_SCFSR_TEND));
  SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;

  /* FIFO�˶����������ޤ��Ԥ� */
  while ( SCIF.SCFDR.WORD & 0x1000 );

  /* ��ʸ���񤭹��� */
  SCIF.SCFTDR = (unsigned char)code;

  /* ��ʸ������ */
  while ((( i = SCIF.SCFSR.WORD) & (SCIF_SCFSR_TEND|SCIF_SCFSR_TDFE)) != 
	  (SCIF_SCFSR_TEND|SCIF_SCFSR_TDFE));
  SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;

  /* FIFO����,�Ǹ�ΰ�ʸ����������λ���Ԥ� */
//  while ( SCIF.SCFDR.WORD & 0x1f00);
//  while (!(SCIF.SCFSR.WORD & SCIF_SCFSR_TEND));
}

void scif_init( VP_INT exf){}

void scif_puts( char  *p)
{
  int  i;

  do {
    /* FIFO�˶����������ޤ��Ԥ� */
    while ( (i = (SCIF.SCFDR.WORD & 0x1f00)>>8) == 16 );
    /* FIFO�ζ�����ʬ�����񤭹��� */
    for ( i = 16-i; i>0 && *p ; i--)
      SCIF.SCFTDR = *p++;
    while (!(( i = SCIF.SCFSR.WORD) & SCIF_SCFSR_TEND));
    SCIF.SCFSR.WORD = i & ~SCIF_SCFSR_TEND;
  } while ( *p);

  /* FIFO����,�Ǹ�ΰ�ʸ����������λ���Ԥ� */
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
