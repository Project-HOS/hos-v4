/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ アラームハンドラ                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_alm_h__
#define __HOS_V4__knl_alm_h__



#include "knl_hos.h"
#include "knl_tim.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_ALMID		1					/* アラームハンドラIDの最小値 */
#define KERNEL_TMAX_ALMID		(TMIN_ALMID + kernel_almcb_cnt - 1)
											/* アラームハンドラIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* アラームハンドラコントロールブロック(ROM部) */
typedef struct t_kernel_almcb_rom
{
	ATR    almatr;		/* アラームハンドラ属性 */
	VP_INT exinf;		/* アラームハンドラの拡張情報 */
	FP     almhdr;		/* アラームハンドラの起動番地 */
} T_KERNEL_ALMCB_ROM;

/* アラームハンドラコントロールブロック(RAM部) */
typedef struct t_kernel_almcb_ram
{
	T_KERNEL_TIM timobj;		/* タイマオブジェクトを継承 */
	RELTIM       lefttim;		/* アラームハンドラのを次に起動する時刻までの時間 */
	const T_KERNEL_ALMCB_ROM *almcb_rom;	/* アラームハンドラコントロールブロックROM部へのポインタ */
} T_KERNEL_ALMCB_RAM;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* アラームハンドラ */
extern       T_KERNEL_ALMCB_RAM *kernel_almcb_ram_tbl[];	/* アラームハンドラコントロールブロックテーブル */
extern const INT kernel_almcb_cnt;							/* アラームハンドラコントロールブロック個数 */

#define KERNEL_ALMID_TO_ALMCB_RAM(almid)	(kernel_almcb_ram_tbl[(almid) - TMIN_ALMID])
															/* アラームハンドラIDからALMCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* アラームハンドラ */
void    kernel_ini_alm(void);								/* アラームハンドラの初期化 */
void    kernel_alm_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* アラームハンドラのタイマハンドラ */
ER      sta_alm(ID almid, RELTIM almtim);					/* アラームハンドラの動作開始 */
ER      stp_alm(ID almid);									/* アラームハンドラの動作停止 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_alm_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
