/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    μカーネル依存情報定義ヘッダ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__mknl_h__
#define __HOS_V4__mknl_h__



#include "itron.h"
#include "hosdenv.h"



/* ------------------------------------------ */
/*                定数定義                    */
/* ------------------------------------------ */

/* タスク優先度の範囲 */
#define TMIN_TPRI			1					/* タスク優先度の最小値 */
#define TMAX_TPRI			(TMIN_TPRI + mknl_rdq_cnt - 1)
												/* タスク優先度の最大値 */


/* システムの状態 */
#define MKNL_TSS_TSK		0x00				/* タスク部実行中 */
#define MKNL_TSS_INDP		0x04				/* タスク独立部実行中 */
#define MKNL_TSS_DDSP		0x01				/* ディスパッチ禁止 (dis_dsp 有効) */
#define MKNL_TSS_DINT		0x02				/* 割り込み禁止(loc_cpu 有効) */
#define MKNL_TSS_DDLY		0x80				/* ディスパッチ遅延中 */

/* タスクの例外処理状態 */
#define MKNL_TTS_RDLY		0x01				/* 例外処理保留状態 */
#define MKNL_TTS_DRAS		0x02				/* 例外処理禁止状態 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* キュー管理ブロック */
typedef struct t_mknl_que
{
	struct t_mknl_tcb *head;	/* キューの先頭 */
} T_MKNL_QUE;


/* μカーネル タスクコントロールブロック */
typedef struct t_mknl_tcb
{
	T_HOSPAC_CTXINF   ctxinf;		/* コンテキスト情報保存ブロック */
	STAT              tskwait;		/* 待ち要因 */
	UB                tskstat;		/* タスクの状態 */
	UB                texstat;		/* 例外処理の状態 */
	PRI               tskpri;		/* 現在の優先度 */
	ER_UINT           ercd;			/* 待ち解除要因用エラーコード */
	VP_INT            data;			/* 汎用データ領域 */
	struct t_mknl_que *que;			/* 属しているキュー  */
	struct t_mknl_tcb *next;		/* キューでの次のTCB */
	struct t_mknl_tcb *prev;		/* キューでの前のTCB */
	struct t_mknl_tcb *tm_next;		/* タイムアウトキューの次のTCB */
	struct t_mknl_tcb *tm_prev;		/* タイムアウトキューの前のTCB */
	RELTIM            diftim;		/* 直前のTCBとのタイムアウトまでの時間差 */
} T_MKNL_TCB;


/* タイムアウト管理用構造体 */
typedef struct t_mknl_timout
{
	T_MKNL_TCB *mtcb;		/* タイムアウト待ちのタスク */
	RELTIM     diftim;		/* 配列直前の待ちタスクとの時間差 */
} T_MKNL_TIMOUT;



/* ------------------------------------------ */
/*              外部変数宣言                  */
/* ------------------------------------------ */

/* システム管理 */
extern STAT            mknl_ctx_stat;		/* システムのコンテキスト状態 */
extern T_MKNL_TCB      *mknl_run_mtcb;		/* 実行中タスクコントロールブロック */

/* アイドルループ管理 */
extern T_HOSPAC_CTXINF mknl_idlctx;			/* アイドルループのコンテキスト */
extern const VP        mknl_idl_stk;		/* アイドルループのスタック */
extern const SIZE      mknl_idl_stksz;		/* アイドルループのスタックサイズ */

/* タスク管理 */
extern T_MKNL_QUE      mknl_rdq_tbl[];		/* レディーキューテーブル */
extern const INT       mknl_rdq_cnt;		/* レディーキュー個数 */

extern       INT       mknl_timout_tskcnt;	/* タイムアウト待ち行列のタスク個数 */

/* タイムアウト管理 */
extern T_MKNL_TCB      *mknl_timout_head;	/* タイムアウトキューの先頭 */


/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* μカーネルのサービスコールは原則 mknl_sys_loc() で */
/* ロックされた状態で呼び出されること                 */

/* システム制御 */
void    mknl_ini_sys(void);									/* μカーネルシステムの初期化 */
void    mknl_sta_startup(void);								/* スタートアップルーチンの開始処理 */
void    mknl_ext_startup(void);								/* スタートアップルーチンの終了処理 */
void    mknl_idl_loop(void);								/* アイドルループ */

/* タスク制御 */
#define mknl_ini_tsk(mtcb)	do { (mtcb)->tskstat = TTS_DMT; } while (0)
															/* タスクの初期化(マクロ関数) */
void    mknl_sta_tsk(T_MKNL_TCB *mtcb, VP_INT exinf,
							FP task, PRI tskpri,
							SIZE stksz, VP stk);			/* タスクの開始 */
void    mknl_ter_tsk(T_MKNL_TCB *mtcb);						/* タスクの終了 */
void    mknl_chg_pri(T_MKNL_TCB *mtcb, PRI tskpri);			/* タスク優先度変更 */
void    mknl_wai_tsk(T_MKNL_TCB *mtcb, STAT tskwait);		/* タスクの待ち */
void    mknl_wup_tsk(T_MKNL_TCB *mtcb, ER_UINT ercd);		/* タスクの待ち解除 */
void    mknl_sus_tsk(T_MKNL_TCB *mtcb);						/* タスクの強制待ち */
void    mknl_rsm_tsk(T_MKNL_TCB *mtcb);						/* タスクの強制待ち解除 */
void    mknl_rot_rdq(PRI tskpri);							/* タスク優先順位の回転 */
ER_UINT mknl_exe_dsp(void);									/* タスクディスパッチの実行 */
void    mknl_dly_dsp(void);									/* 遅延していたディスパッチの実行 */
T_MKNL_TCB* mknl_srh_top(void);								/* レディーキュー先頭のタスクを探す */
#define mknl_get_run_tsk()		(mknl_run_mtcb)				/* 実行中タスクの取得(マクロ関数) */
#define mknl_get_pri(mtcb)		((PRI)(mtcb)->tskpri)		/* タスク優先度取得(マクロ関数) */
#define mknl_get_tskstat(mtcb)	((STAT)(mtcb)->tskstat)		/* タスク状態取得(マクロ関数) */
#define mknl_get_tskwait(mtcb)	((STAT)(mtcb)->tskwait)		/* 待ち要因取得(マクロ関数) */

void    kernel_task_entry(VP_INT exinf);					/* タスクのエントリーポイント(カーネル側で用意すること) */


/* タスク例外処理 */
void    mknl_ras_tex(T_MKNL_TCB *mtcb);						/* タスク例外処理の要求 */
void    mknl_exe_tex(void);									/* タスク例外処理の実行 */
#define mknl_dis_tex(mtcb)	\
	do { (mtcb)->texstat |= MKNL_TTS_DRAS; } while (0)		/* タスク例外処理の禁止 */
#define mknl_ena_tex(mtcb)	\
	do { (mtcb)->texstat &= ~MKNL_TTS_DRAS; } while (0)		/* タスク例外処理の許可 */
#define mknl_sns_tex()	\
	((mknl_run_mtcb == NULL || (mknl_run_mtcb->texstat & MKNL_TTS_DRAS)) ? TRUE: FALSE)
															/* タスク例外処理禁止状態の参照 */

void    kernel_tex_entry(void);								/* タスク例外処理エントリーポイント(カーネル側で用意すること) */
	

/* システム制御 */
#define mknl_loc_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_dis_int(); } } while (0)
															/* システムのロック(マクロ関数) */
#define mknl_unl_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_ena_int(); } } while (0)
															/* システムのロック解除(マクロ関数) */
#define mknl_dis_int()	do { hospac_dis_int(); } while (0)	/* 割り込み禁止 */
#define mknl_ena_int()	do { hospac_ena_int(); } while (0)	/* 割り込み許可 */
#define mknl_sta_ind()	do { mknl_ctx_stat |= MKNL_TSS_INDP; } while (0)
															/* 非タスク部の開始(マクロ関数) */
#define mknl_ext_ind()	do { mknl_ctx_stat &= ~MKNL_TSS_INDP; } while (0)
															/* 非タスク部の終了(マクロ関数) */
#define mknl_loc_cpu()	do { mknl_ctx_stat |= MKNL_TSS_DINT; } while (0)
															/* CPUのロック(マクロ関数) */
#define mknl_unl_cpu()	do { mknl_ctx_stat &= ~MKNL_TSS_DINT; } while (0)
															/* CPUのロック解除(マクロ関数) */
#define mknl_dis_dsp()	do { mknl_ctx_stat |= MKNL_TSS_DDSP; } while (0)
															/* ディスパッチの禁止(マクロ関数) */
#define mknl_ena_dsp()	do { mknl_ctx_stat &= ~MKNL_TSS_DDSP; } while (0)
															/* ディスパッチの許可(マクロ関数) */
#define mknl_sns_ctx()	((mknl_ctx_stat & MKNL_TSS_INDP) ? TRUE : FALSE)
															/* コンテキストの参照(マクロ関数) */
#define mknl_sns_loc()	((mknl_ctx_stat & MKNL_TSS_DINT) ? TRUE : FALSE)
															/* CPUロック状態の参照(マクロ関数) */
#define mknl_sns_dsp()	((mknl_ctx_stat & MKNL_TSS_DDSP) ? TRUE : FALSE)
															/* ディスパッチ禁止状態の参照(マクロ関数) */
#define mknl_sns_dpn()	((mknl_ctx_stat & MKNL_TSS_DDLY) ? TRUE : FALSE)
															/* ディスパッチ保留状態の参照(マクロ関数) */
#define mknl_sns_wai()	((mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT)) ? TRUE : FALSE)
															/* 待ち状態移行可能参照(マクロ関数) */


/* キュー操作 */
#define mknl_ini_que(que)	do { (que)->head = NULL; } while (0)
void    mknl_clr_que(T_MKNL_QUE *que);						/* キューの削除 */
															/* キューの初期化 */
void    mknl_add_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb, ATR atr);
															/* タスクをキューに追加 */
void    mknl_adf_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* タスクをFIFO順でキューに追加 */
void    mknl_adp_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* タスクを優先度順でキューに追加 */
void    mknl_rmv_que(T_MKNL_TCB *mtcb);						/* タスクをキューから取り除く */
void    mknl_rot_que(T_MKNL_QUE *que);						/* レディーキューの回転 */
#define mknl_ref_qhd(que)	((que)->head)					/* キューの先頭タスクの参照(マクロ関数) */
#define mknl_ref_nxt(que, mtcb)		\
		((mtcb)->next != (que)->head ? (que)->head : NULL)	/* 次のキューを取得 */

/* タイムアウト待ち行列 */
void    mknl_tic_tmout(RELTIM tictim);						/* タイムアウトにタイムティック供給 */
ER      mknl_add_tmout(T_MKNL_TCB *mtcb, RELTIM tmout);		/* タイムアウト待ち行列にタスクを追加 */
void    mknl_rmv_tmout(T_MKNL_TCB *mtcb);					/* タイムアウト待ち行列からタスクを取り除く */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__mknl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
