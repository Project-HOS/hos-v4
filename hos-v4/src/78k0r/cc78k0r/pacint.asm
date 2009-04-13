;	------------------------------------------------------------------------
;		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
;			プロセッサ抽象化コンポーネント (78K0Rコア用)
;
;									Copyright (C) 1998-2009 by Project HOS
;									http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;		$PROCESSOR	(f1166a0)			; ra78k0r 起動オプションで指定

		$INCLUDE	(78k0rregs.inc)		; ラベル定義とマクロ定義
		$INCLUDE	(78k0r/vectasm.inc)	; 割込みベクタ番号定義

		DSEG
		EXTRN		_kernel_int_sp
		EXTRN		_kernel_int_cnt
		EXTRN		_kernel_int_ssp

		DSEG	SADDR
		PUBLIC		intno
intno:	DW			(1)
;	************************************************************************
;		割込みハンドラ
;		__interrupt void int_handler( void )
;		saddr intnoに割込み番号を入れてこの関数を呼び出すこと
;		割込み番号は include/78k0r/vectasm.inc と vect.h にて定義（同一）
;	************************************************************************
		CSEG	BASE
		EXTRN		_kernel_sta_int
		EXTRN		_kernel_exe_int
		EXTRN		_kernel_end_int

		PUBLIC		_int_handler
_int_handler:
	; レジスタ退避
		push	ax
	; 多重割込みの判別
		movw	ax, !_kernel_int_cnt
		cmpw	ax, #0000H
		bnz		$_mul_int
		nop
	; 割り込みネストカウンタ加算
		incw	!_kernel_int_cnt
	; スタックの退避と再定義
		movw	ax, sp
		movw	!_kernel_int_ssp, ax
		movw	ax, !_kernel_int_sp
		movw	sp, ax
	; 割り込み開始処理呼び出し
		call	!!_kernel_sta_int
	; 割り込みハンドラ呼び出し
		movw	ax, intno
		call	!!_kernel_exe_int
	; スタックの復帰
		movw	ax, !_kernel_int_ssp
		movw	sp, ax
	; 割り込みネストカウンタクリア
		decw	!_kernel_int_cnt
	; 割り込み終了処理呼び出し
		call	!!_kernel_end_int
	; レジスタ復帰
		pop		ax
		reti
	; ======== 多重割り込み ========
_mul_int:
	; 割り込みネストカウンタ加算
		incw	!_kernel_int_cnt
	; 割り込みハンドラ呼び出し
		movw	ax, intno
		call	!!_kernel_exe_int
	; 割り込みネストカウンタ減算
		decw	!_kernel_int_cnt
	; レジスタ復帰
		pop		ax
		reti

		END
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
