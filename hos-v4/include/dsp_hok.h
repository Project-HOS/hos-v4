/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    デバッグ支援  ディスパッチフック                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__dsp_hok_h__
#define __HOS_V4__dsp_hok_h__



/* ディスパッチフックマクロ */
#ifdef _HOS_DSP_HOK_ENABLE
#ifndef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK_ENABLE
#endif
#ifndef _HOS_INT_HOK_ENABLE
#define _HOS_INT_HOK_ENABLE
#endif
#endif

/* タスクスイッチ フックマクロの定義 */
#ifdef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK()	_hos_tsw_hok()	/* 有効 */
#else
#define _HOS_TSW_HOK()					/* 無効 */
#endif

/* 割り込み フックマクロの定義 */
#ifdef _HOS_INT_HOK_ENABLE
#define _HOS_INTSTA_HOK(intno)	_hos_intsta_hok(intno)	/* 有効 */
#define _HOS_INTEXT_HOK(intno)	_hos_intext_hok(intno)
#else
#define _HOS_INTSTA_HOK(intno)							/* 無効 */
#define _HOS_INTEXT_HOK(intno)
#endif

/* ディスパッチタイプ定義 */
#define _HOS_DSPTYPE_TSKSWC		1	/* タスクスイッチ発生 */
#define _HOS_DSPTYPE_STAINT		2	/* 割り込み処理開始 */
#define _HOS_DSPTYPE_EXTINT		3	/* 割り込み処理終了 */

/* フックマスク */
#define _HOS_HOKMSK_TSW			0x01	/* タスクスイッチフック */
#define _HOS_HOKMSK_INT			0x02	/* 割り込みフック */


/* ディスパッチ情報 */
typedef struct t_dbg_dspinf
{
	UW  time;		/* 時間 */
	INT type;		/* 発生事象 */
	INT id;			/* ID */
} T_DBG_DSPINF;



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* 制御関数 */
void _hosdbg_ini_dsphok(T_DBG_DSPINF dspinf[], INT infcnt);	/* フック処理初期化 */
void _hosdbg_sta_dsphok(INT mask);							/* フック処理開始 */
void _hosdbg_stp_dsphok(void);								/* フック処理停止 */

/* ログ読み出し関数 */
T_DBG_DSPINF *_hosdbg_red_fst(void);		/* 読み出し開始 */
T_DBG_DSPINF *_hosdbg_red_nxt(void);		/* 次を読み出し */

/* ディスパッチフック関数 */
void _hos_tsw_hok(void);			/* タスクスイッチ フック */
void _hos_intsta_hok(INTNO intno);	/* 割り込み開始 フック */
void _hos_intext_hok(INTNO intno);	/* 割り込み終了 フック */

/* ユーザー作成関数 */
UW   _hosdbg_get_tim(void);			/* 高精度時間取得 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__dsp_hok_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
