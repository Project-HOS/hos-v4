/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ 時間管理                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tim_h__
#define __HOS_V4__knl_tim_h__



#include "knl_hos.h"



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* タイマオブジェクト構造体 */
typedef struct t_kernel_tim
{
	struct t_kernel_tim *next;
	struct t_kernel_tim *prev;
	FP                  timhdr;
} T_KERNEL_TIM;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* システム時刻管理 */
extern const UW kernel_tic_deno;				/* コンフィギュレーションで TIC_DENO を設定 */
extern const UW kernel_tic_div;					/* コンフィギュレーションで TIC_NUME / TIC_DENO を設定 */
extern const UW kernel_tic_mod;					/* コンフィギュレーションで TIC_NUME % TIC_DENO を設定 */
extern UW       kernel_tic_cnt;					/* タイムティック用カウンタ */
extern SYSTIM   kernel_systim;					/* システム時刻 */


/* タイマリスト管理 */
extern T_KERNEL_TIM *kernel_tml_head;	/* タイマリスト先頭位置 */
extern T_KERNEL_TIM *kernel_tml_ptr;	/* タイマリストポインタ */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* システム時刻管理 */
void    kernel_ini_tim(void);						/* 時間管理機能の初期化 */
ER      set_tim(const SYSTIM *p_systim);			/* システム時刻の設定 */
ER      get_tim(SYSTIM *p_systim);					/* システム時刻の取得 */
ER      isig_tim(void);								/* タイムティックの供給 */

/* タイマリスト操作 */
void    kernel_add_tml(T_KERNEL_TIM *timobj);		/* タイマオブジェクトのリストへの追加 */
void    kernel_rmv_tml(T_KERNEL_TIM *timobj);		/* タイマオブジェクトのリストからの削除 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tim_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
