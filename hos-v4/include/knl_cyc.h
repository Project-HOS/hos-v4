/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ 周期ハンドラ                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_cyc_h__
#define __HOS_V4__knl_cyc_h__



#include "knl_hos.h"
#include "knl_tim.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_CYCID		1					/* 周期ハンドラIDの最小値 */
#define TMAX_CYCID		(TMIN_CYCID + kernel_cyccb_cnt - 1)
											/* 周期ハンドラIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* 周期ハンドラコントロールブロック(ROM部) */
typedef struct t_kernel_cyccb_rom
{
	ATR    cycatr;		/* 周期ハンドラ属性 */
	VP_INT exinf;		/* 周期ハンドラの拡張情報 */
	FP     cychdr;		/* 周期ハンドラの起動番地 */
	RELTIM cyctim;		/* 周期ハンドラの起動周期 */
} T_KERNEL_CYCCB_ROM;

/* 周期ハンドラコントロールブロック(RAM部) */
typedef struct t_kernel_cyccb_ram
{
	T_KERNEL_TIM timobj;		/* タイマオブジェクトを継承 */
	RELTIM       lefttim;		/* 周期ハンドラのを次に起動する時刻までの時間 */
	const T_KERNEL_CYCCB_ROM *cyccb_rom;	/* 周期ハンドラコントロールブロックROM部へのポインタ */
} T_KERNEL_CYCCB_RAM;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* 周期ハンドラ */
extern       T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[];	/* 周期ハンドラコントロールブロックテーブル */
extern const INT kernel_cyccb_cnt;							/* 周期ハンドラコントロールブロック個数 */

#define KERNEL_CYCID_TO_CYCCB_RAM(cycid)	(kernel_cyccb_ram_tbl[(cycid) - TMIN_CYCID])
															/* 周期ハンドラIDからCYCCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* 周期ハンドラ */
void    kernel_ini_cyc(void);								/* 周期ハンドラの初期化 */
void    kernel_cyc_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* 周期ハンドラのタイマハンドラ */
ER      sta_cyc(ID cycid);									/* 周期ハンドラの動作開始 */
ER      stp_cyc(ID cycid);									/* 周期ハンドラの動作停止 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_cyc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
