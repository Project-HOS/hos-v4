/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*  OS ������                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include "kernel.h"
#include "ostimer.h"
#include "sh7750.h"

/* OS�ѥ����޽���� */
void ostim_init(VP_INT exinf)
{
  /* �����޽���� */
  /* ���,TMU0������ߤ��� */
  TMU.TSTR.BYTE &= 0xfe;

  /*
   * UNF=0|00|UNIE=1|CKEG1=0|CKEG0=0|TPSC=000
   * P��/4=50MHz/4=12.5MHz�ǥ������,�����ߵ���
   */
  TMU0.TCR.WORD = 0x20;
  TMU0.TCOR = TMU0.TCNT = (((UH)(INT)exinf) * 100) >> 3;
  /* TMU0 �����󥿥������� */
  TMU.TSTR.BYTE |= 0x01;
}


/* �����ߥϥ�ɥ饵��ץ� */
void ostim_hdr(VP_INT exinf)	/* OS�������ѥϥ�ɥ� */
{
  /* ��������ե��ե饰���ꥢ */
  TMU0.TCR.WORD &= 0xfeff;

  isig_tim();		/* ������ƥ��å��ζ��� */
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
