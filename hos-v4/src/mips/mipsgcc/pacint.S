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
		la		k0, kernel_int_cnt
		lw		k1, (k0)
		beql	k1, $0, _int_l01
		nop
		addiu	k1, k1, 1
		sw		k1, (k0)
		beql	$0, $0, _int_l02
		nop
_int_l01:
		addiu	k1, k1, 1
		sw		k1, (k0)
		# スタックの退避
		la		k0, kernel_int_ssp
		sw		sp, (k0)
		la		k0, kernel_int_sp
		lw		sp, (k0)
		# 割り込み開始処理呼び出し
		la		k0, kernel_sta_int
		jal		k0
		nop
#
#	例外内容の確認と分岐
#
_int_l02:
		.set noreorder
		mfc0	k0, CP0_CAUSE
		mfc0	k1, CP0_STATUS
		nop
		and		k0, k0, k1
#		sw		k0, kernel_int_reg_k0	# 今後の割込みのために保存
	#
	#	IP7 : CP0 INT7 (例外処理 HOSのタスク切り替え)
	#
_irq_ip7:
		andi	k1, k0, (1 << 15)
		beq		k1, $0, _irq_ip2
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_IP7			# 割込みベクタ番号
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	#	IP2 : External INT2 (例外処理 外部割込み)
	#
_irq_ip2:
#		lw		k0, kernel_int_reg_k0
		andi	k1, k0, (1 << 10)
		beq		k1, $0, _irq_ip1
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_IP2
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# IP1 : Software INT1 (例外処理 ソフトウェア割込み１)
	#
_irq_ip1:
#		lw		k0, kernel_int_reg_k0
		andi	k1, k0, (1 <<  9)
		beq		k1, $0, _irq_ip0
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_IP1
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# IP0 : Software INT0 (例外処理 ソフトウェア割込み０)
	#
_irq_ip0:
#		lw		k0, kernel_int_reg_k0
		andi	k1, k0, (1 << 8)
		beq		k1, $0, _exccode
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_IP0
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 内の処理
	#
_exccode:
#		lw		k0, kernel_int_reg_k0
		srl		k0, k0, 2
		andi	k0, k0, 0x001F			# ExcCode のみ取り出す
#		sw		k0, kernel_int_reg_k0
	#
	# ExcCode 1 Mod (例外処理 TLB変更例外)
	#
_exccode_1:
		slti	k1, k0, 1
		bnez	k1, _exccode_2
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode1
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 2 TLBL (例外処理 TLB不一致例外 ロードまたは命令フェッチ)
	#
_exccode_2:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 2
		bnez	k1, _exccode_3
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode2
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 3 TLBS (例外処理 TLB不一致例外 ストア）
	#
_exccode_3:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 3
		bnez	k1, _exccode_4
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode3
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 4 AdEL (例外処理 アドレス・エラー例外 ロードまたは命令フェッチ）
	#
_exccode_4:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 4
		bnez	k1, _exccode_5
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode4
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 5 AdES (例外処理 アドレス・エラー例外 ストア）
	#
_exccode_5:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 5
		bnez	k1, _exccode_6
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode5
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 6 IBE (例外処理 バス・エラー例外 命令フェッチ）
	#
_exccode_6:
	#	lw		k0, kernel_int_reg_k0
	#	slti	k1, k0, 6
	#	bnez	k1, _exccode_6
	#	nop
	#	# 割り込み番号を引数して実行処理呼び出し
	#	la		k0, kernel_exe_int
	#	li		a0, HOS_VN_ExcCode6
	#	jal		k0
	#	nop
	#
	# ExcCode 7 DBE (例外処理 バス・エラー例外 データのロードまたはストア）
	#
_exccode_7:
	#	lw		k0, kernel_int_reg_k0
	#	slti	k1, k0, 7
	#	bnez	k1, _exccode_8
	#	nop
	#	# 割り込み番号を引数して実行処理呼び出し
	#	la		k0, kernel_exe_int
	#	li		a0, HOS_VN_ExcCode7
	#	jal		k0
	#	nop
	#
	# ExcCode 8 Sys (例外処理 システム・コール例外)
	#
_exccode_8:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 8
		bnez	k1, _exccode_9
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode8
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 9 Bp (例外処理 ブレークポイント例外)
	#
_exccode_9:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 9
		bnez	k1, _exccode_10
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode9
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 10 RI (例外処理 予約命令例外)
	#
_exccode_10:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 10
		bnez	k1, _exccode_11
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode10
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 11 CpU (例外処理 コプロセッサ使用不可例外)
	#
_exccode_11:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 11
		bnez	k1, _exccode_12
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode11
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 12 Ov (例外処理 演算オーバフロー例外)
	#
_exccode_12:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 12
		bnez	k1, _exccode_13
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode12
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 13 Tr (例外処理 トラップ例外)
	#
_exccode_13:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 13
		bnez	k1, _exccode_15
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode13
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 15 FPE (例外処理 浮動小数点例外)
	#
_exccode_15:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 15
		bnez	k1, _exccode_23
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode15
		jal		k0
		nop
		beql	$0, $0, _ret_from_irq
		nop
	#
	# ExcCode 23 Watch (例外処理 ウォッチ例外)
	#
_exccode_23:
#		lw		k0, kernel_int_reg_k0
		slti	k1, k0, 23
		bnez	k1, _ret_from_irq
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, HOS_VN_ExcCode23
		jal		k0
		nop
		.set	reorder
	#
	# レジスタ復帰処理と eret
	#
_ret_from_irq:
		la		k0, kernel_int_cnt
		lw		k1, (k0)
		addiu	k1, k1, -1
		sw		k1, (k0)
		bne		k1, $0, _int_l12
		nop

_int_l11:
		# スタックの復帰
		la		k0, kernel_int_ssp
		lw		sp, (k0)
		# IE=0, EXL=0にセット（割り込みは禁止のまま)
#		mfc0	k0, CP0_STATUS
#		nop
#		la		k1, 0xF1FFFFF8			# ERL=0,IE=0,EXL=0
#		and		k0, k1, k0
#		mtc0	k0, CP0_STATUS
#		nop
		# 割り込み終了処理呼び出し
		la		k0, kernel_end_int
		jal		k0
		nop
		# IE=1, EXL=1にセット（割り込みは禁止のまま)
#		mfc0	k0, CP0_STATUS
#		nop
#		la		k1, 0xF1FFFFFB
#		and		k0, k1, k0				# ERL=0
#		la		k1, 0x00000003			# IE=1, EXL=1
#		or		k0, k1, k0
#		mtc0	k0, CP0_STATUS
#		nop
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
kernel_int_reg_k0:
		nop
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
