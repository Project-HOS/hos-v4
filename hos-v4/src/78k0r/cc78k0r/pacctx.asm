;	------------------------------------------------------------------------
;		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
;			プロセッサ抽象化コンポーネント (78K0Rコア用)
;
;									Copyright (C) 1998-2009 by Project HOS
;									http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;		$PROCESSOR	(f1166a0)			; ra78k0r 起動オプションで指定
		$INCLUDE	(78k0rregs.inc)		; ラベル定義とマクロ定義
;	************************************************************************
;		実行コンテキストの作成
;		void hospac_cre_ctx_asm(
;			T_HOSPAC_CTXINF	*pk_ctxinf,	; 作成するコンテキスト	ax		(2)
;			VP_INT			exinf,		; 実行時パラメータ		[sp+4]	(4)
;			FP				task,		; task起動番地			[sp+8]	(4)
;			VP				stkp)		; スタックポインタ		[sp+12]	(2)
;	************************************************************************
		CSEG	BASE
		PUBLIC	_hospac_cre_ctx_asm
_hospac_cre_ctx_asm:
		push	hl
		push	de
		push	ax

		movw	de, ax					; pk_ctxinf
		movw	ax, [sp+12+6]			; stkp
		subw	ax, #pt_size
		movw	hl, ax
	; スタックポインタの保存（設定）
	;	movw	[hl+pt_sp], ax
	; ES, CS レジスタの状態保存
		mov		a, cs
		xch		a, x
		mov		a, es
		movw	[hl+pt_es], ax			; CS, ES レジスタを退避
	; 実行時のパラメータ保存
$IF (__USE_RB__)
		mov		a, psw
		and		a, #10000000B
		clrb	x
		movw	[hl+pt_psw], ax
		movw	ax, [sp+4+6]
		movw	[hl+pt_ax0], ax			; 実行時のパラメータ保存 (RBS=0前提)
		movw	ax, [sp+6+6]
		movw	[hl+pt_bc0], ax			; 実行時のパラメータ保存 (RBS=0前提)
$ELSE
		movw	ax, [sp+4+6]
		movw	[hl+pt_ax], ax			; 実行時のパラメータ保存
		movw	ax, [sp+6+6]
		movw	[hl+pt_bc], ax			; 実行時のパラメータ保存
$ENDIF
	; task起動番地保存
		movw	ax, [sp+8+6]
		movw	[hl+pt_adrs], ax
		mov		a, [sp+10+6]
		mov		[hl+(pt_adrs+2)], a
	; コンテキスト保存
		movw	ax, hl
		movw	[de], ax

		pop		ax
		pop		de
		pop		hl
		ret								; 呼び出し元へ戻る
		nop
;	************************************************************************
;		実行コンテキストの切替
;		void hospac_swi_ctx(
;			T_HOSPAC_CTXINF *pk_pre_ctxinf, コンテキストの保存先	ax
;			T_HOSPAC_CTXINF *pk_nxt_ctxinf) 切り替えるコンテキスト	[sp+4]
;	************************************************************************
		DSEG	SADDRP
prectx:	DW		(1)						; 現在のコンテキストの保存先
nxtctx:	DW		(1)						; 切り替えるコンテキスト
		CSEG	BASE
		PUBLIC	_hospac_swi_ctx
_hospac_swi_ctx:
		movw	prectx, ax
		movw	ax, [sp+4]
		movw	nxtctx, ax
		movw	ax, prectx				; 不要かな？
		pushall							; 全レジスタ退避
		movw	hl, prectx
		movw	ax, sp
		movw	[hl], ax				; spレジスタを管理領域へ退避
		movw	hl, nxtctx
		movw	ax, [hl]
		movw	sp, ax					; 管理領域から spレジスタを復帰
		popall							; 全レジスタ復帰
		ret								; コンテキストへジャンプ
		nop

		END
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
