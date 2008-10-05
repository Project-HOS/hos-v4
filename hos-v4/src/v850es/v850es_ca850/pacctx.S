#	------------------------------------------------------------------------
#		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
#			プロセッサ抽象化コンポーネント (V850ES互換コア用)
#
#									Copyright (C) 1998-2008 by Project HOS
#									http://sourceforge.jp/projects/hos/
#	------------------------------------------------------------------------
#		.option		cpu F3716			-- as850 起動オプションで指定
		.include	"v850esregs.inc"	-- ラベル定義とマクロ定義
#	************************************************************************
#		実行コンテキストの作成
#		void hospac_cre_ctx_asm(
#			T_HOSPAC_CTXINF		*pk_ctxinf,		作成するコンテキスト	r6
#			VP_INT				exinf,			実行時パラメータ		r7
#			FP					task,			task起動番地			r8
#			VP					stkp)			スタックポインタ		r9
#	************************************************************************
		.globl		_hospac_cre_ctx_asm
		.text
		.align	4
_hospac_cre_ctx_asm:
		mov		0xFFFFFFFC, r10
		and		r10, r9
		addi	-pt_ssf, r9, r10
		st.w	r10, 0[r6]				-- コンテキストのスタックポインタ保存
		st.w	r4, pt_r4[r10]			-- r4 グローバルポインタを格納
		st.w	r5, pt_r5[r10]			-- r5 テキストポインタを格納
		st.w	r7, pt_r6[r10]			-- r6退避場所に、実行パラメータ r7 を格納
		st.w	r8, pt_lp[r10]			-- lp(r31)退避場所に、taskアドレスを格納
		st.w	r9, pt_sp[r10]			-- sp(r3)退避場所に、伸長前のスタックポインタを格納
	.if 0	-- debug
		st.w	r0, pt_eipsw[r10]		-- 割込み時状態退避レジスタeipsw は、0 とする。
		st.w	r0, pt_psw[r10]			-- プログラムステートワードは、0 とする。
	.endif
	.if 0	-- debug
		stsr	eipc, r11				-- 割込み時状態退避レジスタ
		st.w	r11, pt_eipc[r10]
	.endif
	.if 0	-- debug
		stsr	eipsw, r11				-- 割込み時状態退避レジスタ
		st.w	r11, pt_eipsw[r10]
	.endif
	.if 0	-- debug
		stsr	fepc, r11				-- NMI 割込状態退避レジスタ
		st.w	r11, pt_fepc[r10]
	.endif
	.if 0	-- debug
		stsr	fepsw, r11				-- NMI 割込状態退避レジスタ
		st.w	r11, pt_fepsw[r10]
	.endif
	.if 0	-- debug
		stsr	psw, r11				-- プログラムステートワード
		st.w	r11, pt_psw[r10]
	.endif
		stsr	ctpc, r11				-- CALLT実行時状態退避レジスタ
		st.w	r11, pt_ctpc[r10]
		stsr	ctpsw, r11				-- CALLT実行時状態退避レジスタ
		st.w	r11, pt_ctpsw[r10]
	.if 0	-- debug
		stsr	ctbp, r11				-- CALLTベースポインタ
		st.w	r11, pt_ctbp[r10]
	.endif
		jmp		[lp]					-- 呼び出し元lp(r31)へ戻る
		nop
#	************************************************************************
#		実行コンテキストの切替
#		void hospac_swi_ctx(
#			T_HOSPAC_CTXINF *pk_pre_ctxinf, 現在のコンテキストの保存先	r6
#			T_HOSPAC_CTXINF *pk_nxt_ctxinf) 切り替えるコンテキスト		r7
#	************************************************************************
		.globl		_hospac_swi_ctx
		.text
		.align	4
_hospac_swi_ctx:
		pushall							-- 全レジスタ退避
		st.w	sp, 0[r6]				-- sp(r3) レジスタを管理領域へ退避
		ld.w	0[r7], sp				-- 管理領域から sp(r3)レジスタを復帰
		popall							-- 全レジスタ復帰
		jmp		[lp]					-- コンテキストへジャンプ
		nop
#	------------------------------------------------------------------------
#		Copyright (C) 1998-2008 by Project HOS
#	------------------------------------------------------------------------
