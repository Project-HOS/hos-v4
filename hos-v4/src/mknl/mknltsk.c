/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タスク制御                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"
#include "kernel.h"



/* タスクの開始 */
void mknl_sta_tsk(
		T_MKNL_TCB *mtcb,					/* μカーネルタスクコントロールブロック */
		VP_INT     exinf,					/* タスクの拡張情報 */
		FP         task,					/* タスクの起動番地 */
		PRI        tskpri,					/* タスクの起動時優先度 */
		SIZE       stksz,					/* タスクのスタック領域のサイズ */
		VP         stk)						/* タスクのスタック領域の先頭番地 */
{
	/* 実行コンテキストの作成 */
	mtcb->data = exinf;
	hospac_cre_ctx(&mtcb->ctxinf, exinf, task, stksz, stk);

	/* タスクの状態設定 */
	mtcb->tskstat = TTS_RDY;	/* レディー状態に設定 */
	mtcb->texstat = 0;			/* 例外状態初期化 */
	mtcb->tskpri  = tskpri;		/* 優先度設定 */
	mtcb->tskwait = 0;			/* 待ち要因初期化 */

	/* レディーキューに設定 */
	mknl_add_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
}


/* タスクの終了 */
void mknl_ext_tsk(
				T_MKNL_TCB *mtcb)	/* 終了させるタスク */
{
	/* タイムアウトキューにあれば削除 */
	mknl_del_tmout(mtcb);		

	/* タスクキューから外す */
	if ( mtcb->que != NULL )
	{
		mknl_del_que(mtcb);
	}

	mtcb->tskstat = TTS_DMT;	/* 休止状態に設定 */
	mtcb->tskwait = 0;			/* 待ち要因クリア */

	/* 実行コンテキストの削除 */
	hospac_del_ctx(&mtcb->ctxinf);
}



/* タスク優先度変更 */
void mknl_chg_pri(
				T_MKNL_TCB *mtcb,	/* 優先度を変更するタスク */
				PRI tskpri)			/* 設定する優先度 */
{
	/* 優先度変更 */
	if ( !(mtcb->tskstat & TTS_WAI) )
	{
		/* 待ち状態でなければレディーキューに繋ぎなおす */
		mknl_del_que(mtcb);
		mknl_add_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
	}
	mtcb->tskpri = tskpri;
}


/* タスクの待ち設定 */
void mknl_wai_tsk(
		T_MKNL_TCB *mtcb,		/* 待ち状態にするタスク */
		STAT        tskwait)	/* 待ち要因 */
{
	/* 待ち状態に設定 */
	mknl_del_que(mtcb);		/* レディーキューから外す */
	mtcb->tskstat = TTS_WAI;
	mtcb->tskwait = tskwait;
}


/* タスクの待ち解除 */
void mknl_wup_tsk(
		T_MKNL_TCB *mtcb,	/* スリープ解除するタスク */
		ER_UINT    ercd)	/* 解除するタスクに渡すエラーコード */
{
	/* タスクのスリープ解除 */
	mtcb->ercd = ercd;
	mknl_add_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_RDY;	/* 待ち解除なら実行可能状態 */
	}
	else
	{
		mtcb->tskstat = TTS_SUS;	/* 二重待ち状態なら強制待ち状態 */
	}
	mtcb->tskwait = 0;		/* 待ち要因クリア */
}


/* タスクの強制待ち */
void mknl_sus_tsk(
		T_MKNL_TCB *mtcb)	/* 強制待ち状態にするタスク */
{
	/* タスクの強制待ち(レディーキューからは外さない) */
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_WAS;
	}
	else
	{
		mtcb->tskstat = TTS_SUS;
	}
}


/* タスクの強制待ち解除 */
void mknl_rsm_tsk(
		T_MKNL_TCB *mtcb)	/* 強制待ち解除するタスク */
{
	/* 強制待ち解除 */
	if ( mtcb->tskstat == TTS_WAS )
	{
		mtcb->tskstat = TTS_WAI;		/* 二重待ち状態なら待ち状態 */
	}
	else
	{
		mtcb->tskstat = TTS_RDY;		/* 強制待ち状態なら実行可能状態 */
	}
}


/* タスクディスパッチの実行 */
ER_UINT mknl_exe_dsp(void)
{
	T_HOSPAC_CTXINF *ctxinf_top;
	T_HOSPAC_CTXINF *ctxinf_run;
	T_MKNL_TCB *mtcb_top;
	T_MKNL_TCB *mtcb_run;

	/* コンテキストチェック */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP) )
	{
		/* ディスパッチ実行可能状態で無ければ保留する */
		mknl_ctx_stat |= MKNL_TSS_DDLY;	/* ディスパッチ遅延フラグをセット */
		return E_OK;
	}

	/* 最高優先度の実行可能タスクを探す */
	mtcb_top = mknl_srh_top();

	mtcb_run = mknl_run_mtcb;	/* 現在のタスクをローカルに退避 */

	/* 実行中タスクが同じなら何もしない(アイドルからアイドルも含む） */
	if ( mtcb_top == mtcb_run )
	{
		if ( mtcb_run == NULL )
		{
			return E_OK;
		}
		return mtcb_run->ercd;
	}

	/* アイドルタスク実行中でないかチェック */
	if ( mtcb_run == NULL )
	{
		/* アイドルならアイドルコンテキストを設定 */
		ctxinf_run = &mknl_idlctx;
	}
	else
	{
		/* 実行中のコンテキストを設定 */
		ctxinf_run = &mtcb_run->ctxinf;
	}

	/* 次に実行するタスクがあるかどうかチェック */
	if ( mtcb_top == NULL )
	{
		/* 実行先が無ければアイドルコンテキストを設定 */
		mknl_run_mtcb = NULL;
		ctxinf_top    = &mknl_idlctx;
	}
	else
	{
		/* 実行先のタスクを実行中タスクとして登録 */
		mknl_run_mtcb     = mtcb_top;
		mtcb_top->tskstat = TTS_RDY;
		
		/* 実行先のコンテキストを設定 */
		ctxinf_top = &mtcb_top->ctxinf;
	}

	/* タスクコンテキストスイッチ実行 */
	hospac_swi_ctx(ctxinf_run, ctxinf_top);

	if ( mtcb_run == NULL )
	{
		return E_OK;
	}

	return mtcb_run->ercd;
}



/* 遅延していたディスパッチの実行 */
void mknl_dly_dsp(void)
{
	/* システムコンテキストチェック */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP) )
	{
		return;		/* ディスパッチ実行可能でなければ保留続行 */
	}

	/* 遅延フラグチェック */
	if ( !(mknl_ctx_stat & MKNL_TSS_DDLY) )
	{
		return;		/* 遅延が無ければ何もしない */
	}

	/* 遅延フラグクリア */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* 遅延ディスパッチ実行 */
	mknl_exe_dsp();
}


/* レディーキュー先頭のタスクを探す */
T_MKNL_TCB* mknl_srh_top(void)
{
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_head;
	INT i;

	/* 最高優先度の実行可能タスクを探す */
	for ( i = 0; i < mknl_rdq_cnt; i++ )	/* 優先度の高いキューから順に検索 */
	{
		if ( mknl_rdq_tbl[i].head != NULL )
		{
			/* 強制待ち状態で無い先頭タスクを探す */
			mtcb_head = mknl_rdq_tbl[i].head;
			mtcb      = mtcb_head;
			do
			{
				if ( !(mtcb->tskstat & TTS_SUS) )
				{
					return mtcb;	/* 見つけたタスクを返す */
				}
				mtcb = mtcb->next;
			} while ( mtcb != mtcb_head);
		}
	}

	return NULL;	/* 実行可能タスク無し */
}


/* タスク優先順位の回転 */
void mknl_rot_rdq(
		PRI tskpri)		/* 優先順位を回転する対象の優先度 */
{
	mknl_rot_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI]);
}



/* タスク例外処理の要求 */
void mknl_ras_tex(
		T_MKNL_TCB *mtcb)	/* 例外処理を要求するタスク */
{
	if ( mtcb == mknl_run_mtcb && !(mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* 実行中タスクで、例外禁止でなければ例外発行 */
		do
		{
			mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mtcb->texstat != 0 );	/* 例外要因がなくなるまでループ */
	}
	else
	{
		/* 例外を保留する */
		mtcb->texstat &= MKNL_TTS_RDLY;
	}
}


/* タスク例外処理の実行 */
void mknl_exe_tex(void)
{
	if (  (mknl_run_mtcb->texstat & MKNL_TTS_RDLY)
				&& !(mknl_run_mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* 例外保留があり、例外禁止でなければ例外発行 */
		do
		{
			mknl_run_mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mknl_run_mtcb->texstat != 0 );	/* 例外要因がなくなるまでループ */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
