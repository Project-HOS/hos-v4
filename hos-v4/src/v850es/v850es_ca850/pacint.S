#	------------------------------------------------------------------------
#		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
#			プロセッサ抽象化コンポーネント (V850ES互換コア用)
#
#									Copyright (C) 1998-2008 by Project HOS
#									http://sourceforge.jp/projects/hos/
#	------------------------------------------------------------------------
#		.option		cpu F3716			-- as850 起動オプションで指定
		.include	"v850esregs.inc"	-- ラベル定義とマクロ定義
		.include	"v850es/vectasm.inc"
										-- 割込みベクタ番号定義
		.extern		_kernel_int_sp, 4
#	************************************************************************
#		割込みハンドラ
#		__interrupt void int_handler( void )
#		r2 レジスタに割込み番号を入れてこの関数を呼び出すこと
#		割込み番号は include/v850es/vectasm.inc と vect.h にて定義（同一）
#	************************************************************************
		.text
		.globl _int_handler
		.align	4
_int_handler:
	# レジスタ退避
		pushall
	# 多重割込みの判別
		ld.w	$_kernel_int_cnt, r10
		cmp		r0, r10
		jne		_mul_int
		nop
	# 割り込みネストカウンタ加算
		add		1, r10
		st.w	r10, $_kernel_int_cnt
	# スタックの退避と再定義
		st.w	sp, $_kernel_int_ssp
		ld.w	#_kernel_int_sp, sp
	# 割り込み開始処理呼び出し
		jarl	_kernel_sta_int, lp
	# 割り込みハンドラ呼び出し
		mov		r2, r6					-- r2 割込み番号
		jarl	_kernel_exe_int, lp
	# 割り込みネストカウンタクリア
		st.w	r0, $_kernel_int_cnt
	# スタックの復帰
		ld.w	$_kernel_int_ssp, sp
	# 割り込み終了処理呼び出し
		jarl	_kernel_end_int, lp
	# レジスタ復帰
		popall
		reti
	# ======== 多重割り込み ========
_mul_int:
	# 割り込みネストカウンタ加算
		add		1, r10
		st.w	r10, $_kernel_int_cnt
	# 割り込みハンドラ呼び出し
		mov		r2, r6					-- r2 割込み番号
		jarl	_kernel_exe_int, lp
	# 割り込みネストカウンタ減算
		ld.w	$_kernel_int_cnt, r10
		add		-1, r10
		st.w	r10, $_kernel_int_cnt
	# レジスタ復帰
		popall
		reti
#	------------------------------------------------------------------------
#		Copyright (C) 1998-2008 by Project HOS
#	------------------------------------------------------------------------
