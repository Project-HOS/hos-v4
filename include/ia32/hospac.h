/* ------------------------------------------------------------------------*/
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (IA32用)                                   */
/*      プロセッサ抽象化コンポーネント共通定義                                   */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hospac_h__
#define __HOS_V4__IA32__hospac_h__
#include "pic.h"                 /*  割込みコントローラ関連処理  */
#if defined(__GNUC__ ) 
#include "ia32gcc/linkage.h"     /*  gcc 固有リンケージ定義  */
#include "ia32gcc/ioport.h"      /*  I/O ポート関連処理  */
#include "ia32gcc/hosexp.h"      /*  割り込み例外関連定義  */
#include "ia32gcc/descriptor.h"  /*  IA32ディスクリプタ関連定義  */
#include "ia32gcc/switch.h"  /*  IA32ディスクリプタ関連定義  */
#include "ia32gcc/idle.h"    /*  IA32アイドル処理関連定義  */
#else
#error "IA32 port can not support your compiler."
#endif  /*  __GNUC__  */
#include "itron.h"


/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */
/* IA32固有 割り込み管理機構 */
typedef UH		IMSK;		/* 割り込みマスクパターン */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* スタックポインタ保存領域 */
} T_HOSPAC_CTXINF;


/* ------------------------------------------ */
/*                マクロ定義                  */
/* ------------------------------------------ */
#define MAX_IRQ_NR  16  /*  外部割込みの最大数  */


/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif
extern void hospac_ini_sys(void);  /* プロセッサ抽象化コンポーネントの初期化 */

/* 実行コンテクスト作成処理 */
extern void hospac_cre_ctx(
        T_HOSPAC_CTXINF *pk_ctxinf,  /* コンテキスト情報格納先の先頭番地 */
        VP_INT          exinf,       /* 起動時引数 */
        FP              task,        /* 起動番地 */
        SIZE            stksz,       /* スタックサイズ */
        VP              stk          /* スタック先頭番地 */
      );

  /* 実行コンテキストの切替 */
extern void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
			   T_HOSPAC_CTXINF *pk_nxt_ctxinf);
/* IA32固有 割り込み管理機構 */
ER   chg_imsk(IMSK imsk);		/* 割り込みマスク指定 */
ER   get_imsk(IMSK *p_imsk);		/* 割り込みマスクの参照 */

ER   _kernel_ia32__send_eoi(UW irq);	/* 割り込み完了通知 */


#ifdef __cplusplus
}
#endif

#endif  /*  __HOS_V4__IA32__hospac_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
