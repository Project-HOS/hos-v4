/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ 時間管理                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tim_h__
#define __HOS_V4__knl_tim_h__



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
	RELTIM lefttim;		/* 周期ハンドラのを次に起動する時刻までの時間 */
	STAT   cycstat;		/* 周期ハンドラの動作状態 */
	const T_KERNEL_CYCCB_ROM  *cyccbrom;	/* 周期ハンドラコントロールブロックROM部へのポインタ */
} T_KERNEL_CYCCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* システム時刻管理 */
extern const UW     kernel_tic_deno;	/* コンフィギュレーションで TIC_DENO を設定 */
extern const UW     kernel_tic_div;		/* コンフィギュレーションで TIC_NUME / TIC_DENO を設定 */
extern const UW     kernel_tic_mod;		/* コンフィギュレーションで TIC_NUME % TIC_DENO を設定 */
extern       UW     kernel_tic_cnt;		/* タイムティック用カウンタ */
extern       SYSTIM kernel_systim;		/* システム時刻 */


/* 周期ハンドラ */
extern       T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[];	/* 周期ハンドラコントロールブロックテーブル */
extern const INT kernel_cyccb_cnt;							/* 周期ハンドラコントロールブロック個数 */

#define KERNEL_CYCID_TO_CYCCB_RAM(cycid)	(kernel_cyccb_ram_tbl[(cycid) - TMIN_CYCID])
															/* 周期ハンドラIDからCYCCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* システム時刻管理 */
void    kernel_ini_tim(void);						/* 時間管理機能の初期化 */
ER      set_tim(const SYSTIM *p_systim);			/* システム時刻の設定 */
ER      get_tim(SYSTIM *p_systim);					/* システム時刻の取得 */
ER      isig_tim(void);								/* タイムティックの供給 */


/* 周期ハンドラ */
void    kernel_ini_cyc(void);						/* 周期ハンドラの初期化 */
ER      sta_cyc(ID cycid);							/* 周期ハンドラの動作開始 */
ER      stp_cyc(ID cycid);							/* 周期ハンドラの動作停止 */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tim_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
