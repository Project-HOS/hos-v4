/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (MIPS3互換コア用)                      */
/*    割り込みハンドラ                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "mipsregs.h"
#include "mips/vect.h"

		.global int_handler				# 割り込みハンドラ
		.global inthdl					# crt0.c 用
		.global einthdl					# crt0.c 用
		.global inthdljp				# crt0.c 用
# **************************************************************************
# *  割り込みハンドラ (0x80000800 へ crt0.c にてコピーされる）
# *  内部で割り込み要因を判定して登録したハンドラを呼び出す。
# *  現在はタイマ割り込みしかサポートしていない。
# **************************************************************************

		.text
		.align	4
int_handler:
inthdl:
		pushall							# レジスタ退避

		# 多重割込みの判別
		la		t8, kernel_int_cnt
		lw		t9, (t8)
		beql	t9, $0, _int_l01
		nop
		addiu	t9, t9, 1
		sw		t9, (t8)
		beql	$0, $0, _int_l02
		nop
_int_l01:
		addiu	t9, t9, 1
		sw		t9, (t8)
		# スタックの退避
		la		t8, kernel_int_ssp
		sw		sp, (t8)
		la		t8, kernel_int_sp
		lw		sp, (t8)
		# 割り込み開始処理呼び出し
		la		t8, kernel_sta_int
		jal		t8
		nop
#
#	例外内容の確認と分岐
#
_int_l02:
		.set noreorder
		mfc0	t8, CP0_CAUSE
		mfc0	t9, CP0_STATUS
		nop
		nop
		and		t8, t8, t9
#		sw		t8, kernel_int_reg_t8	# 今後の割込みのために保存
	#
	#	IP7 : CP0 INT7 (例外処理 HOSのタスク切り替え)
	#
_irq_ip7:
		andi	t9, t8, (1 << 15)
		beq		t9, $0, _irq_ip2
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_IP7			# 割込みベクタ番号
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	#	IP2 : External INT2 (例外処理 外部割込み)
	#
_irq_ip2:
#		lw		t8, kernel_int_reg_t8
		andi	t9, t8, (1 << 10)
		beq		t9, $0, _irq_ip1
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_IP2
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# IP1 : Software INT1 (例外処理 ソフトウェア割込み１)
	#
_irq_ip1:
#		lw		t8, kernel_int_reg_t8
		andi	t9, t8, (1 <<  9)
		beq		t9, $0, _irq_ip0
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_IP1
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# IP0 : Software INT0 (例外処理 ソフトウェア割込み０)
	#
_irq_ip0:
#		lw		t8, kernel_int_reg_t8
		andi	t9, t8, (1 << 8)
		beq		t9, $0, _exccode
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_IP0
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 内の処理
	#
_exccode:
#		lw		t8, kernel_int_reg_t8
		srl		t8, t8, 2
		andi	t8, t8, 0x001F			# ExcCode のみ取り出す
#		sw		t8, kernel_int_reg_t8
	#
	# ExcCode 1 Mod (例外処理 TLB変更例外)
	#
_exccode_1:
		slti	t9, t8, 1
		bnez	t9, _exccode_2
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode1
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 2 TLBL (例外処理 TLB不一致例外 ロードまたは命令フェッチ)
	#
_exccode_2:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 2
		bnez	t9, _exccode_3
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode2
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 3 TLBS (例外処理 TLB不一致例外 ストア）
	#
_exccode_3:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 3
		bnez	t9, _exccode_4
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode3
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 4 AdEL (例外処理 アドレス・エラー例外 ロードまたは命令フェッチ）
	#
_exccode_4:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 4
		bnez	t9, _exccode_5
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode4
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 5 AdES (例外処理 アドレス・エラー例外 ストア）
	#
_exccode_5:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 5
		bnez	t9, _exccode_6
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode5
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 6 IBE (例外処理 バス・エラー例外 命令フェッチ）
	#
_exccode_6:
	#	lw		t8, kernel_int_reg_t8
	#	slti	t9, t8, 6
	#	bnez	t9, _exccode_6
	#	nop
	#	# 割り込み番号を引数して実行処理呼び出し
	#	la		t8, kernel_exe_int
	#	li		a0, HOS_VN_ExcCode6
	#	jal		t8
	#	nop
	#
	# ExcCode 7 DBE (例外処理 バス・エラー例外 データのロードまたはストア）
	#
_exccode_7:
	#	lw		t8, kernel_int_reg_t8
	#	slti	t9, t8, 7
	#	bnez	t9, _exccode_8
	#	nop
	#	# 割り込み番号を引数して実行処理呼び出し
	#	la		t8, kernel_exe_int
	#	li		a0, HOS_VN_ExcCode7
	#	jal		t8
	#	nop
	#
	# ExcCode 8 Sys (例外処理 システム・コール例外)
	#
_exccode_8:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 8
		bnez	t9, _exccode_9
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode8
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 9 Bp (例外処理 ブレークポイント例外)
	#
_exccode_9:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 9
		bnez	t9, _exccode_10
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode9
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 10 RI (例外処理 予約命令例外)
	#
_exccode_10:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 10
		bnez	t9, _exccode_11
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode10
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 11 CpU (例外処理 コプロセッサ使用不可例外)
	#
_exccode_11:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 11
		bnez	t9, _exccode_12
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode11
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 12 Ov (例外処理 演算オーバフロー例外)
	#
_exccode_12:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 12
		bnez	t9, _exccode_13
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode12
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 13 Tr (例外処理 トラップ例外)
	#
_exccode_13:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 13
		bnez	t9, _exccode_15
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode13
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 15 FPE (例外処理 浮動小数点例外)
	#
_exccode_15:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 15
		bnez	t9, _exccode_23
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode15
		jal		t8
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 23 Watch (例外処理 ウォッチ例外)
	#
_exccode_23:
#		lw		t8, kernel_int_reg_t8
		slti	t9, t8, 23
		bnez	t9, _ret_from_irq
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		t8, kernel_exe_int
		li		a0, HOS_VN_ExcCode23
		jal		t8
		nop
		.set	reorder
	#
	# レジスタ復帰処理と eret
	#
_ret_from_irq:
		la		t8, kernel_int_cnt
		lw		t9, (t8)
		addiu	t9, t9, -1
		sw		t9, (t8)
		bne		t9, $0, _int_l12
		nop

_int_l11:
		# スタックの復帰
		la		t8, kernel_int_ssp
		lw		sp, (t8)
		# IE=0, EXL=0にセット（割り込みは禁止のまま)
		mfc0	t8, CP0_STATUS
		nop
		la		t9, 0xF1FFFFF8			# ERL=0,IE=0,EXL=0
		and		t8, t9, t8
		mtc0	t8, CP0_STATUS
		nop
		# 割り込み終了処理呼び出し
		la		t8, kernel_end_int
		jal		t8
		nop
		# IE=1, EXL=1にセット（割り込みは禁止のまま)
		mfc0	t8, CP0_STATUS
		nop
		la		t9, 0xF1FFFFFB
		and		t8, t9, t8				# ERL=0
		la		t9, 0x00000003			# IE=1, EXL=1
		or		t8, t9, t8
		mtc0	t8, CP0_STATUS
		nop
_int_l12:
		popall							# レジスタ復帰
		eret
einthdl:
# **************************************************************************
# *  0x80000180の例外処理発生時にinthdlへ処理を移行するための細工
# *  crt0.c にてジャンプ命令をコピーし実現する。
# **************************************************************************
		.text
		.align	4
inthdljp:								# 0x80000180 へコピー(crt0.cにて)
		j		0x80000800
		nop
# **************************************************************************
# *  例外処理発生時の CP0_STATUS & CP0_CAUSE を保存するための変数
# **************************************************************************
		.data
		.align	4
kernel_int_reg_t8:
		nop
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
