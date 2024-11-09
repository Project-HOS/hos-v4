/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (MIPS4互換コア用)                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "mipsregs.h"

		.global hospac_dis_int			# 割り込み禁止
		.global hospac_ena_int			# 割り込み許可
		.global hospac_cre_ctx_asm		# 実行コンテキストの作成
		.global hospac_swi_ctx			# 実行コンテキストの切替
/***************************************************************************
 *	割り込み禁止
 *	void hospac_dis_int(void)
 *		ステータス・レジスタのIEビットを0にする
 ***************************************************************************/
		.text
		.align	4
hospac_dis_int:
		mfc0	t0, CP0_STATUS			# CP0_STATUS を t0 にロード
		la		t1, 0xF1FFFFF8			# ERL=0, IE=0, EXL=0
		and		t0, t1, t0
		mtc0	t0, CP0_STATUS			# CP0_STATUS にストア
		nop
		jr		ra
		nop
/***************************************************************************
 *	割り込み許可
 *	void hospac_ena_int(void)
 *		ステータス・レジスタのIEビットを1にする
 ***************************************************************************/
		.text
		.align	4
hospac_ena_int:
		mfc0	t0, CP0_STATUS			# CP0_STATUS を t0 にロード
		la		t1, 0xF1FFFFFB			# ERL=0
		and		t0, t1, t0
		la		t1, 0x00000001			# IE =1
		or		t0, t1, t0
		mtc0	t0, CP0_STATUS			# CP0_STATUS にストア
		nop
		jr		ra
		nop
#if defined(__USE_CTX_ENTRY__)
/***************************************************************************
 *  実行コンテキストエントリーアドレス
 *	void ctx_entry(
 *  	VP_INT				exinf,			実行時パラメータ		a0
 *		FP					task)			task アドレス			a1
 ***************************************************************************/
		.text
		.align	4
ctx_entry:
		j		a1
		nop
#endif
/***************************************************************************
 *  実行コンテキストの作成
 *  void hospac_cre_ctx_asm(
 *  	T_HOSPAC_CTXINF		*pk_ctxinf,		作成するコンテキスト	a0
 *  	VP_INT				exinf,			実行時パラメータ		a1
 *		FP					task,			task起動番地			a2
 *  	VP					stkp)			スタックポインタ		a3
 ***************************************************************************/
		.text
		.align	4
hospac_cre_ctx_asm:
		la		t0, 0xFFFFFFF8
		and		a3, a3, t0				# 下位 3bit の強制 0 に変更（丸め実施）
		move	t0, a3                  # スタックポインタを退避
		subu	a3, a3, 288             # スタックの伸張（4*72=288バイト）
		sw		a1,  4*4(a3)            # a0退避場所に、実行パラメータ a1 を格納
		sw		t0, 29*4(a3)            # sp退避場所に、伸長前のスタックポインタを格納
#if defined(__USE_CTX_ENTRY__)
		sw		a2,  5*4(a3)            # 実行アドレスの格納
		la		t0, ctx_entry           # ctx_entry をリターンアドレスに設定
		sw		t0, 31*4(a3)			# ra退避場所に、ctx_entry アドレスを格納
#else
		sw		a2, 31*4(a3)			# ra退避場所に、taskアドレスを格納
#endif
		mfc0	t0, CP0_STATUS          # CP0_STATUS を t0 レジスタにコピー
		sw		a3, (a0)                # コンテキストのスタックポインタ保存
		sw		t0, 36*4(a3)			# CP0_STATUS を格納
		jr		ra                      # 呼び出し元へ戻る
		nop
/***************************************************************************
 *  実行コンテキストの切替
 *  void hospac_swi_ctx(
 *  	T_HOSPAC_CTXINF *pk_pre_ctxinf, 現在のコンテキストの保存先
 *  	T_HOSPAC_CTXINF *pk_nxt_ctxinf) 切り替えるコンテキスト
 ***************************************************************************/
		.text
		.align	4
hospac_swi_ctx:
		pushall							# 全レジスタ退避
		sw		sp, (a0)				# sp レジスタを管理領域へ退避
		lw		sp, (a1)				# 管理領域から spレジスタを復帰
		popall							# 全レジスタ復帰
		jr		ra						# コンテキストへジャンプ
		nop
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
