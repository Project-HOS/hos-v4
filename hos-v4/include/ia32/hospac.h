/* ------------------------------------------------------------------------*/
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (IA32用)                                   */
/*      プロセッサ抽象化コンポーネント共通定義                                   */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hospac_h__
#define __HOS_V4__IA32__hospac_h__
#include "pic.h"         /*  割込みコントローラ関連処理  */
#include "ioport.h"      /*  I/O ポート関連処理  */
#include "hosexp.h"      /*  割り込み例外関連定義  */
#include "descriptor.h"  /*  IA32ディスクリプタ関連定義  */
#include "itron.h"


/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */
/* IA32固有 割り込み管理機構 */
typedef UW		IMSK;		/* 割り込みマスクパターン */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* スタックポインタ保存領域 */
} T_HOSPAC_CTXINF;


/* ------------------------------------------ */
/*                マクロ定義                  */
/* ------------------------------------------ */
#define MAX_IRQ_NR  16  /*  外部割込みの最大数  */

/*  タスクスイッチング  */
#define __hos_pac_ia32_do_task_switch(current_p, next_p) \
	__asm__ __volatile__(                            \
        "pushfl     \n\t"                                \
        "pushl %%ebx\n\t"                                \
        "pushl %%esi\n\t"                                \
        "pushl %%edi\n\t"                                \
        "pushl %%ebp\n\t"                                \
	"pushl $1f\n\t"                                  \
	"movl %%esp, (%0)\n\t" /* update stack val */    \
	"movl (%1), %%esp\n\t" /* get next  */           \
	"ret\n\t"                                        \
        "1:\tpopl %%ebp\n\t"                             \
        "popl %%edi\n\t"                                 \
        "popl %%esi\n\t"                                 \
        "popl %%ebx\n\t"                                 \
        "popfl\n\t"                                      \
	: /* no output */                                \
	: "r" (current_p), "r" (next_p):"memory" )


/*  コンテキスト積み込み  */
#define __hos_pac_ia32_prep_ini_stack(spp, start_func,finalizer,arg)  \
	  do{                                                         \
          __asm__ __volatile__("subl $0xc,(%0)\n\t"                   \
                               "movl (%0),%%ecx\n\t"                     \
                               "movl %1,(%%ecx)\n\t"   /* func  */       \
                               "movl %2,4(%%ecx)\n\t"   /* ext_tsk  */   \
                               "movl %3,8(%%ecx)\n\t"   /* arg */        \
                               :/* No input */                           \
			       :"r"(spp),                                \
			        "r"(start_func),"r"(finalizer),"r"(arg)  \
                               :"ecx");                                  \
          }while(0)

#define hospac_del_ctx(pk_ctxinf)	/* 実行コンテキストの削除 */

/*  アイドル時処理 
 *  電力消費低減のためにhlt命令を発行
 */
#define hospac_idle()	__asm__ __volatile__("hlt\n\t")  

#define hospac_dis_int()  __asm__ __volatile__("cli\n\t")  /* 割り込み禁止 */

#define hospac_ena_int()  __asm__ __volatile__("sti\n\t")  /* 割り込み許可 */

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

ER   send_eoi(UB irq);		        /* 割り込み完了通知 */


#ifdef __cplusplus
}
#endif

#endif  /*  __HOS_V4__IA32__hospac_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
