/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μITRON4.0 標準ヘッダ                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__itron_h__
#define __HOS_V4__itron_h__



/* ------------------------------------ */
/*          データ型定義                */
/* ------------------------------------ */

typedef signed char		B;			/* 符号付き8ビット整数 */
typedef signed short	H;			/* 符号付き16ビット整数 */
typedef signed long		W;			/* 符号付き32ビット整数 */

typedef unsigned char	UB;			/* 符号無し8ビット整数 */
typedef unsigned short 	UH;			/* 符号無し16ビット整数 */
typedef unsigned long	UW;			/* 符号無し32ビット整数 */

typedef signed char		VB;			/* データタイプが定まらない8ビットの値 */
typedef signed short	VH;			/* データタイプが定まらない16ビットの値 */
typedef signed long		VW;			/* データタイプが定まらない32ビットの値 */

typedef void			*VP;		/* データタイプが定まらないものへのポインタ */
typedef void			(*FP)();	/* プログラムの起動番地（ポインタ） */

typedef signed   int	INT;		/* プロセッサに自然なサイズの符号付き整数(16bit以上) */
typedef unsigned int	UINT;		/* プロセッサに自然なサイズの符号無し整数(16bit以上) */

typedef INT		BOOL;		/* 真偽値 */

typedef INT		FN;			/* 機能コード */
typedef INT		ER;			/* エラーコード */
typedef INT		ID;			/* オブジェクトのID番号 */
typedef UH		ATR;		/* オブジェクトの属性 */
typedef UH		STAT;		/* オブジェクトの状態 */
typedef UH		MODE;		/* サービスコールの動作モード */
typedef INT		PRI;		/* 優先度 */
typedef UW		SIZE;		/* メモリ領域のサイズ */
typedef W		TMO;		/* タイムアウト指定 */
typedef UW		RELTIM;		/* 相対時間 */

typedef struct t_systim		/* システム時刻 */
{
	UW ltime;				/* 下位 32bit */
	UH utime;				/* 上位 16bit */
} SYSTIM;

typedef long	VP_INT;		/* VP または INT */

typedef ER		ER_BOOL;	/* ER または BOOL */

typedef W		ER_UINT;	/* ER または UINT */

typedef INT		ER_ID;		/* ER または ID */

typedef UH		TEXPTN;		/* タスク例外要因のパターン */

typedef UH		FLGPTN;		/* フラグパターン */

typedef INT     EXCNO;		/* CPU例外ハンドラ番号 */

typedef INT		INHNO;		/* 割り込みハンドラ番号 */
typedef INT		INTNO;		/* 割り込み番号 */



/* ------------------------------------ */
/*             定数定義                 */
/* ------------------------------------ */

/* 一般 */
#ifdef NULL		/* C言語標準ヘッダとの競合回避 */
#undef NULL
#endif

#ifdef __cplusplus
#define NULL		0			/* 無効ポインタ */
#else
#define NULL		((void *)0)	/* 無効ポインタ */
#endif

#define TRUE		1			/* 真 */
#define FALSE		0			/* 偽 */
#define E_OK		0			/* 正常終了 */


/* オブジェクト属性 */
#define TA_NULL		0			/* オブジェクト属性を指定しない */
#define TA_HLNG		0x00		/* 高級言語用のインターフェースで処理単位を起動 */
#define TA_ASM		0x01		/* アセンブリ言語用のインターフェースで処理単位を起動 */

#define TA_TFIFO	0x00		/* タスクの待ち行列をFIFO順に */
#define TA_TPRI		0x01		/* タスクの待ち行列をタスクの優先度順に */

#define TA_MFIFO	0x00		/* メッセージの待ち行列をFIFO順に */
#define TA_MPRI		0x02		/* メッセージの待ち行列をメッセージの優先度順に */

#define TA_ACT		0x02		/* タスクを起動された状態で生成 */
#define TA_RSTR		0x04		/* 制約タスク */

#define TA_WSGL		0x00		/* イベントフラグを複数のタスクが待つことを許さない */
#define TA_WMUL		0x02		/* イベントフラグを複数のタスクが待つことを許す */
#define TA_CLR		0x04		/* 待ち解除時にイベントフラグをクリア */

#define TA_INHERIT	0x02		/* ミューテックスが優先度継承プロトコルをサポート */
#define TA_CEILING	0x03		/* ミューテックスが優先度上限プロトコルをサポート */

#define TA_STA		0x02		/* 周期ハンドラを動作している状態で生成 */
#define TA_PHS		0x04		/* 周期ハンドラの位相を保存 */


/* タイムアウト指定 */
#define TMO_POL		0			/* ポーリング */
#define TMO_FEVR	(-1)		/* 永久待ち */
#define TMO_NBLK	(-2)		/* ノンブロッキング */


/* サービスコールの動作モード */
#define TWF_ANDW	0x00		/* イベントフラグのAND待ち */
#define TWF_ORW		0x01		/* イベントフラグのOR待ち */


/* オブジェクトの状態 */
#define TTS_RUN		0x01		/* 実行状態 */
#define TTS_RDY		0x02		/* 実行可能状態 */
#define TTS_WAI		0x04		/* 待ち状態 */
#define TTS_SUS		0x08		/* 強制待ち状態 */
#define TTS_WAS		0x0c		/* 二重待ち状態 */
#define TTS_DMT		0x10		/* 休止状態 */

#define TTW_SLP		0x0001		/* 起床待ち状態 */
#define TTW_DLY		0x0002		/* 時間経過待ち状態 */
#define TTW_SEM		0x0004		/* セマフォ資源の獲得待ち状態 */
#define TTW_FLG		0x0008		/* イベントフラグ待ち状態 */
#define TTW_SDTQ	0x0010		/* データキューへの送信待ち状態 */
#define TTW_RDTQ	0x0020		/* データキューからの受信待ち状態 */
#define TTW_MBX		0x0040		/* メールボックスからの受信待ち状態 */
#define TTW_MTX		0x0080		/* ミューテックスのロック待ち状態 */
#define TTW_SMBF	0x0100		/* メッセージバッファへの送信待ち状態 */
#define TTW_RMBF	0x0200		/* メッセージバッファからの受信待ち状態 */
#define TTW_CAL		0x0400		/* ランデブの呼び出し待ち状態 */
#define TTW_ACP		0x0800		/* ランデブの受付待ち状態 */
#define TTW_RDV		0x1000		/* ランデブの終了待ち状態 */
#define TTW_MPF		0x2000		/* 固定長メモリブロックの獲得待ち状態 */
#define TTW_MPL		0x4000		/* 可変長メモリブロックの獲得待ち状態 */

#define TTEX_ENA	0x00		/* タスクの例外処理許可状態 */
#define TTEX_DIS	0x01		/* タスク例外処理禁止状態 */

#define TCYC_STP	0x00		/* 周期ハンドラが動作していない */
#define TCYC_STA	0x01		/* 周期ハンドラが動作している */

#define TALM_STP	0x00		/* アラームハンドラが動作していない */
#define TALM_STA	0x00		/* アラームハンドラが動作している */

#define TOVR_STP	0x00		/* 上限プロセッサ時間が設定されていない */
#define TOVR_STA	0x01		/* 上限プロセッサ時間が設定されている */

/* その他の定数 */
#define TSK_SELF	0			/* 自タスク指定 */
#define TSK_NONE	0			/* 該当するタスクが無い */

#define TPRI_SELF	0			/* 自タスクのベース優先度の指定 */
#define TPRI_INI	0			/* タスクの起動時優先度の指定 */


/* エラーコード */
#define E_SYS		(-5)		/* システムエラー */
#define E_NOSPT		(-9)		/* 未サポート機能 */
#define E_RSFN		(-10)		/* 予約機能コード */
#define E_RSATR		(-11)		/* 予約属性 */
#define E_PAR		(-17)		/* パラメータエラー */
#define E_ID		(-18)		/* 不正ID番号 */
#define E_CTX		(-25)		/* コンテキストエラー */
#define E_MACV		(-26)		/* メモリアクセス違反 */
#define E_OACV		(-27)		/* オブジェクトアクセス違反 */
#define E_ILUSE		(-28)		/* サービスコール不正使用 */
#define E_NOMEM		(-33)		/* メモリ不足 */
#define E_NOID		(-34)		/* ID番号不足 */
#define E_OBJ		(-41)		/* オブジェクト状態エラー */
#define E_NOEXS		(-42)		/* オブジェクト未生成 */
#define E_QOVR		(-43)		/* キューイングオーバーフロー */
#define E_RLWAI		(-49)		/* 待ち状態の強制解除 */
#define E_TMOUT		(-50)		/* ポーリング失敗またはタイムアウト */
#define E_DLT		(-51)		/* 待ちオブジェクトの削除 */
#define E_CLS		(-52)		/* 待ちオブジェクトの状態変化 */
#define E_WBLK		(-57)		/* ノンブロッキング受付け */
#define E_BOVR		(-58)		/* バッファオーバーフロー */


/* IDの範囲(HOS独自) */
#define TMIN_TSKID	1			/* タスクのID番号の最小値 */
#define TMIN_SEMID	1			/* セマフォのID番号の最小値 */
#define TMIN_FLGID	1			/* イベントフラグのID番号の最小値 */
#define TMIN_DTQID	1			/* データキューのID番号の最小値 */
#define TMIN_MBXID	1			/* メールボックスタスクのID番号の最小値 */
#define TMIN_MBFID	1			/* メッセージバッファのID番号の最小値 */
#define TMIN_MPFID	1			/* 固定長メモリプールのID番号の最小値 */
#define TMIN_CYCID	1			/* 周期ハンドラのID番号の最小値 */
#define TMIN_ALMID	1			/* アラームハンドラのID番号の最小値 */
#define TMIN_ISRID	1			/* 割り込みサービスルーチンのID番号の最小値 */



/* ------------------------------------ */
/*           マクロ定義                 */
/* ------------------------------------ */


/* エラーコード取り出し */
#define	MERCD(ercd)		((ER)((B)(ercd)))		/* エラーコードからメインエラーコードを取り出す */
#define	SERCD(ercd)		((ercd) >> 8)			/* エラーコードからサブエラーコードを取り出す */



#endif /* __HOS_V4__itron_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
