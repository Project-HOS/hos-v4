/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ CPU例外ハンドラ管理                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_exc_h__
#define __HOS_V4__knl_exc_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* 割り込み番号の範囲 */
#define TMIN_EXCNO		(kernel_min_excno)	/* CPU例外ハンドラ番号の最小値 */
#define TMAX_EXCNO		(TMIN_EXCNO + kernel_exccb_cnt - 1)
											/* CPU例外ハンドラ番号の最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* CPU例外ハンドラコントロールブロック */
typedef struct t_kernel_exccb
{
	FP exchdr;			/* CPU例外ハンドラの起動番地 */
} T_KERNEL_EXCCB;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/*  CPU例外ハンドラ管理 */
extern T_KERNEL_EXCCB  kernel_exccb_tbl[];	/* CPU例外ハンドラコントロールブロックテーブル */
extern const INT       kernel_exccb_cnt;	/* CPU例外ハンドラ番号数 */
extern const EXCNO     kernel_min_excno;	/* CPU例外ハンドラ番号最小値 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* CPU例外ハンドラ管理 */
void    kernel_sta_exc(void);			/* CPU例外ハンドラの開始 */
void    kernel_end_exc(void);			/* CPU例外ハンドラの終了 */
void    kernel_exe_exc(INTNO excno);	/* CPU例外ハンドラ処理実行 */



#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_exc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
