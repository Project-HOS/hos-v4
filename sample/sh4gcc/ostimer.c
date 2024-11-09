/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*  OS タイマ                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include "kernel.h"
#include "ostimer.h"
#include "sh7750.h"

/* OS用タイマ初期化 */
void ostim_init(VP_INT exinf)
{
  /* タイマ初期化 */
  /* 一応,TMU0を一時停止する */
  TMU.TSTR.BYTE &= 0xfe;

  /*
   * UNF=0|00|UNIE=1|CKEG1=0|CKEG0=0|TPSC=000
   * Pφ/4=50MHz/4=12.5MHzでカウント,割り込み許可
   */
  TMU0.TCR.WORD = 0x20;
  TMU0.TCOR = TMU0.TCNT = (((UH)(INT)exinf) * 100) >> 3;
  /* TMU0 カウンタスタート */
  TMU.TSTR.BYTE |= 0x01;
}


/* 割り込みハンドラサンプル */
void ostim_hdr(VP_INT exinf)	/* OSタイマ用ハンドラ */
{
  /* アンダーフローフラグクリア */
  TMU0.TCR.WORD &= 0xfeff;

  isig_tim();		/* タイムティックの供給 */
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
