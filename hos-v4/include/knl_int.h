/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ 割り込み管理                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_int_h__
#define __HOS_V4__knl_int_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* 割り込み番号の範囲 */
#define KERNEL_TMIN_INTNO	(kernel_min_intno)	/* 割り込み番号の最小値 */
#define KERNEL_TMAX_INTNO	(KERNEL_TMIN_INTNO + kernel_intcb_cnt - 1)
												/* 割り込み番号の最大値 */

/* IDの範囲 */
#define KERNEL_TMIN_ISRID	TMIN_ISRID			/* 割り込みサービスルーチンIDの最小値 */
#define KERNEL_TMAX_ISRID	(KERNEL_TMIN_ISRID + kernel_isrcb_cnt - 1)
												/* 割り込みサービスルーチンIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* 割り込み管理コントロールブロック */
typedef struct t_kernel_intcb
{
	VP_INT exinf;		/* 割り込みサービスルーチンの拡張情報 */
	FP     isr;			/* 割り込みサービスルーチンの起動番地 */
} T_KERNEL_INTCB;


/* 割り込みハンドラの定義用 */
typedef struct t_dinh
{
	ATR inhatr;			/* 割り込みハンドラ属性 */
	FP  inthdr;			/* 割り込みハンドラの起動番地 */
} T_DINH;


/* 割り込みサービスルーチンコントロールブロック */
typedef struct t_kernel_isrcb
{
	INTNO  intno;		/* 割り込み番号 */
} T_KERNEL_ISRCB;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* 割り込み管理 */
extern T_KERNEL_INTCB  kernel_intcb_tbl[];	/* 割り込み管理コントロールブロックテーブル */
extern const INT       kernel_intcb_cnt;	/* 割り込み番号数 */
extern const INTNO     kernel_min_intno;	/* 割り込み番号最小値 */

/* 割り込みサービスルーチン */
extern T_KERNEL_ISRCB* kernel_isrcb_tbl[];	/* 割り込みサービスルーチンコントロールブロックテーブル */
extern const INT       kernel_isrcb_cnt;	/* 割り込みサービスルーチンコントロールブロックの個数 */

/* 割り込み制御変数 */
extern INT kernel_int_cnt;		/* 割り込みネスト回数 */
extern VP  kernel_int_ssp;		/* 割り込み時スタック退避 */

#define KERNEL_INTNO_TO_INTCB(intno)	(kernel_intcb_tbl[(intno) - KERNEL_TMIN_INTNO])


/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* 割り込み制御 */
void    kernel_sta_int(void);						/* 割り込みコンテキスト開始処理 */
void    kernel_end_int(void);						/* 割り込みコンテキスト終了処理 */

/* 割り込み管理 */
void    kernel_exe_int(INTNO intno);				/* 割り込み処理実行 */
ER      dis_int(INTNO intno);						/* 割り込みの禁止 */
ER      ena_int(INTNO intno);						/* 割り込みの許可 */


/* 割り込みハンドラ */
ER      def_inh(INTNO intno, T_DINH *pk_dinh);		/* 割り込みハンドラ定義 */


/* 割り込みサービスルーチン */
/*
ER      cre_isr();
ER      acre_isr();
*/

#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_int_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
