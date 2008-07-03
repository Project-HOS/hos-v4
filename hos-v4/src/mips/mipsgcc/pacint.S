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
#
#	例外内容の確認と分岐
#
		.set noreorder
		mfc0	k0, CP0_CAUSE
		mfc0	k1, CP0_STATUS
		and		k0, k0, k1
	# IP7 : TIMER INTERRUPT
		andi	k1, k0, (1 << 15)
		bnez	k1, _irq_ip7
		nop
	# IP2 : External INT
		andi	k1, k0, (1 << 10)
		bnez	k1, _irq_ip2
		nop
	# IP1 : Software INT1
		andi	k1, k0, (1 <<  9)
		bnez	k1, _irq_ip1
		nop
	# IP0 : Software INT0
		andi	k1, k0, (1 << 8)
		bnez	k1, _irq_ip0
		nop
	# ExcCode 内の処理
		srl		k0, k0, 2
		andi	k0, k0, 0x001F			# ExcCode のみ取り出す
	#	1 	Mod 	TLB変更例外
		slti	k1, k0, 1
		beq		k1, $0, _exccode_1
		nop
	#	2 	TLBL 	TLB不一致例外（ロードまたは命令フェッチ)
		slti	k1, k0, 2
		beq		k1, $0, _exccode_2
		nop
	#	3 	TLBS 	TLB不一致例外（ストア）
		slti	k1, k0, 3
		beq		k1, $0, _exccode_3
		nop
	#	4 	AdEL 	アドレス・エラー例外（ロードまたは命令フェッチ）
		slti	k1, k0, 4
		beq		k1, $0, _exccode_4
		nop
	#	5 	AdES 	アドレス・エラー例外（ストア）
		slti	k1, k0, 5
		beq		k1, $0, _exccode_5
		nop
	#	6 	IBE 	バス・エラー例外（命令フェッチ）
	#	slti	k1, k0, 6
	#	beq		k1, $0, _exccode_6
	#	nop
	#	7 	DBE 	バス・エラー例外（データのロードまたはストア）
	#	slti	k1, k0, 7
	#	beq		k1, $0, _exccode_7
	#	nop
	#	8 	Sys 	システム・コール例外
		slti	k1, k0, 8
		beq		k1, $0, _exccode_8
		nop
	#	9 	Bp		ブレークポイント例外
		slti	k1, k0, 9
		beq		k1, $0, _exccode_9
		nop
	#	10 	RI		予約命令例外
		slti	k1, k0, 10
		beq		k1, $0, _exccode_10
		nop
	#	11 	CpU		コプロセッサ使用不可例外
		slti	k1, k0, 11
		beq		k1, $0, _exccode_11
		nop
	#	12 	Ov		演算オーバフロー例外
		slti	k1, k0, 12
		beq		k1, $0, _exccode_12
		nop
	#	13 	Tr		トラップ例外
		slti	k1, k0, 13
		beq		k1, $0, _exccode_13
		nop
	#	15 	FPE 	浮動小数点例外
		slti	k1, k0, 15
		beq		k1, $0, _exccode_15
		nop
	#	23 	Watch 	ウォッチ例外
		slti	k1, k0, 23
		beq		k1, $0, _exccode_23
		nop
	# ここには来ないはず。。。
		beql	$0, $0, _ret_from_irq
		nop
		.set	reorder
#
#	IP7 例外処理 (HOSのタスク切り替え)
#
_irq_ip7:
		# スタックの退避
		la		k0, kernel_int_ssp
		sw		sp, (k0)
		la		k0, kernel_int_sp
		lw		sp, (k0)
		# 割り込み開始処理呼び出し
		la		k0, kernel_sta_int
		jal		k0
		nop
		# 割り込み番号を引数して実行処理呼び出し
		la		k0, kernel_exe_int
		li		a0, 1					# 割込みベクタ番号 (要検討)
		jal		k0
		nop
		# スタックの復帰
		la		k0, kernel_int_ssp
		lw		sp, (k0)
		# IE=0, EXL=0にセット（割り込みは禁止のまま)
		mfc0	k0, CP0_STATUS
		nop
		la		k1, 0xF1FFFFF8			# ERL=0,IE=0,EXL=0
		and		k0, k1, k0
		mtc0	k0, CP0_STATUS
		nop
		# 割り込み終了処理呼び出し
		la		k0, kernel_end_int
		jal		k0
		nop
		# IE=1, EXL=1にセット（割り込みは禁止のまま)
		mfc0	k0, CP0_STATUS
		nop
		la		k1, 0xF1FFFFFB
		and		k0, k1, k0				# ERL=0
		la		k1, 0x00000003			# IE=1, EXL=1
		or		k0, k1, k0
		mtc0	k0, CP0_STATUS
		nop
		# レジスタ復帰後 eret へ
		beql	$0, $0, _ret_from_irq
		nop
#
#	IP2 例外処理 (外部割込み)
#
_irq_ip2:
		li		k0, 0x80000000
		lw		k1, HOS_VA_IP2(k0)
		beql	k1, $0, _irq_ip2_main
		nop
		jal		k1
		nop
		# レジスタ復帰後 eret へ
		beql	$0, $0, _ret_from_irq
		nop
		# 割込み内容に応じてベクタ番号毎に分岐を実施
_irq_ip2_main:
		li		k0, 0xB8800000
		sh		$0, 0x0B2C(k0)			# io_out16(INTC_INT_ACK,0)
	#
		li		k0, 0xB8800000
		lhu		k1, 0x0B24(k0)			# k1=io_in16(INTC_INT_PENDING)
		andi	k1, k1, (1 << 8)
		beq		k1, $0, _ip2_int7
		nop
	#
	#	INT9(FPGA) 割込み
	#
	#	ここは SEMB1200A独自仕様 (FPGAからの外部割込み)
	#	�� 外部FPGAのPWMユニットによる割込み発生時の処理。
	#	注意）割込み初期化はレベル判定（エッヂではない）
	#	 e.g.; io_out16(INTC_INT_MASK, 0x0100);
	#	       io_out16(INTC_CH9_LEVEL, 15);
	#
_ip2_int9_pwm0:
	# FPGA PWM0 割込み
		li		k0, 0xBE000000			# CS5
		lhu		k1, 0xA6(k0)			# k1 = pwm_unit_get(0,SEMB1200_PWM_INT_STAT2)
		beq		k1, $0, _ip2_int9_pwm1
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_PWM0(k0)
		beq		k1, $0, _end_int9_pwm0
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# PWM0 割込み終了
_end_int9_pwm0:
		li		k0, 0xBE000000			# CS5
		ori		k1, $0, 1				# k1 = 1
		sh		k1, 0xAA(k0)			# pwm_unit_set(0,SEMB1200_PWM_INT_PEND2,1);
	# FPGA PWM1 割込み
_ip2_int9_pwm1:
		li		k0, 0xBE000000			# CS5
		lhu		k1, 0xB6(k0)			# k1 = pwm_unit_get(1,SEMB1200_PWM_INT_STAT2)
		beq		k1, $0, _ip2_int9_pwm2
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_PWM1(k0)
		beq		k1, $0, _end_int9_pwm1
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# PWM1 割込み終了
_end_int9_pwm1:
		li		k0, 0xBE000000			# CS5
		ori		k1, $0, 1				# k1 = 1
		sh		k1, 0xBA(k0)			# pwm_unit_set(1,SEMB1200_PWM_INT_PEND2,1);
	# FPGA PWM2 割込み
_ip2_int9_pwm2:
		li		k0, 0xBE000000			# CS5
		lhu		k1, 0xC6(k0)			# k1 = pwm_unit_get(2,SEMB1200_PWM_INT_STAT2)
		beq		k1, $0, _ip2_int9_pwm3
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_PWM2(k0)
		beq		k1, $0, _end_int9_pwm2
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# PWM2 割込み終了
_end_int9_pwm2:
		li		k0, 0xBE000000			# CS5
		ori		k1, $0, 1				# k1 = 1
		sh		k1, 0xCA(k0)			# pwm_unit_set(2,SEMB1200_PWM_INT_PEND2,1);
	# FPGA PWM3 割込み
_ip2_int9_pwm3:
		li		k0, 0xBE000000			# CS5
		lhu		k1, 0xD6(k0)			# k1 = pwm_unit_get(3,SEMB1200_PWM_INT_STAT2)
		beq		k1, $0, _ip2_int9_uart3_0
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_PWM3(k0)
		beq		k1, $0, _end_int9_pwm3
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# PWM3 割込み終了
_end_int9_pwm3:
		li		k0, 0xBE000000			# CS5
		ori		k1, $0, 1				# k1 = 1
		sh		k1, 0xDA(k0)			# pwm_unit_set(3,SEMB1200_PWM_INT_PEND2,1);
	#
	#	�� 外部FPGAのUART3ユニットによる割込み発生時の処理。
	#
_ip2_int9_uart3_0:
	# FPGA UART3_0 割込み
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 0)
		beq		k1, $0, _ip2_int9_uart3_1
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART30(k0)
		beq		k1, $0, _end_int9_uart30
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_0 割込み終了
_end_int9_uart30:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 0)		# k1 = 1 << 0
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 0))
	# FPGA UART3_1 割込み
_ip2_int9_uart3_1:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 1)
		beq		k1, $0, _ip2_int9_uart3_2
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART31(k0)
		beq		k1, $0, _end_int9_uart31
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_1 割込み終了
_end_int9_uart31:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 1)		# k1 = 1 << 1
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 1))
	# FPGA UART3_2 割込み
_ip2_int9_uart3_2:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 2)
		beq		k1, $0, _ip2_int9_uart3_3
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART32(k0)
		beq		k1, $0, _end_int9_uart32
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_2 割込み終了
_end_int9_uart32:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 2)		# k1 = 1 << 2
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 2))
	# FPGA UART3_3 割込み
_ip2_int9_uart3_3:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 3)
		beq		k1, $0, _ip2_int9_uart3_4
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART33(k0)
		beq		k1, $0, _end_int9_uart33
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_3 割込み終了
_end_int9_uart33:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 3)		# k1 = 1 << 3
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 3))
	# FPGA UART3_4 割込み
_ip2_int9_uart3_4:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 4)
		beq		k1, $0, _ip2_int9_uart3_5
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART34(k0)
		beq		k1, $0, _end_int9_uart34
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_4 割込み終了
_end_int9_uart34:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 4)		# k1 = 1 << 4
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 4))
	# FPGA UART3_5 割込み
_ip2_int9_uart3_5:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 5)
		beq		k1, $0, _ip2_int9_uart3_6
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART35(k0)
		beq		k1, $0, _end_int9_uart35
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_5 割込み終了
_end_int9_uart35:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 5))
	# FPGA UART3_6 割込み
_ip2_int9_uart3_6:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 6)
		beq		k1, $0, _ip2_int9_uart3_7
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART36(k0)
		beq		k1, $0, _end_int9_uart36
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_6 割込み終了
_end_int9_uart36:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 6)		# k1 = 1 << 6
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 6))
	# FPGA UART3_7 割込み
_ip2_int9_uart3_7:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		lhu		k1, 2(k0)				# k1 = io_in16(UART3_INTSTS)
		andi	k1, k1, (1 << 7)
		beq		k1, $0, _end_ip2_int9
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART37(k0)
		beq		k1, $0, _end_int9_uart37
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART3_7 割込み終了
_end_int9_uart37:
		li		k0, 0xBE020000			# CS5 + 0x00020000
		ori		k1, $0, (1 << 7)		# k1 = 1 << 7
		sh		k1, 2(k0)				# io_out16(UART3_INTSTS, (1 << 7))
	# INT9(FPGA) 割込み処理の終了処理
_end_ip2_int9:							# INT9 割込みクリア
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 8)
		sh		k1, 0x0B24(k0)			# io_out16(INTC_INT_PENDING,(1<<8))
	#
	#	INT7(TC#4〜#7) 割込み
	#
_ip2_int7:
		li		k0, 0xB8800000
		lhu		k1, 0x0B24(k0)			# k1=io_in16(INTC_INT_PENDING)
		andi	k1, k1, (1<< 6)
		beq		k1, $0, _ip2_int6
		nop
	# TC#7 割込み
_ip2_int7_tc7:							# TC#7 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0AA0(k0)			# k1 = io_in16( TC7_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC7 割込み ?
		beq		k1, $0, _ip2_int7_tc6
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC7(k0)
		beq		k1, $0, _end_int7_tc7
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#7 割込み終了
_end_int7_tc7:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0AA0(k0)			# INTCONT クリア
	# TC#6 割込み
_ip2_int7_tc6:							# TC#6 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A90(k0)			# k1 = io_in16( TC6_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC6 割込み ?
		beq		k1, $0, _ip2_int7_tc5
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC6(k0)
		beq		k1, $0, _end_int7_tc6
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#6 割込み終了
_end_int7_tc6:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A90(k0)			# INTCONT クリア
	# TC#5 割込み
_ip2_int7_tc5:							# TC#5 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A80(k0)			# k1 = io_in16( TC5_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC5 割込み ?
		beq		k1, $0, _ip2_int7_tc4
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC5(k0)
		beq		k1, $0, _end_int7_tc5
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#5 割込み終了
_end_int7_tc5:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A80(k0)			# INTCONT クリア
	# TC#4 割込み
_ip2_int7_tc4:							# TC#4 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A70(k0)			# k1 = io_in16( TC6_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC4 割込み ?
		beq		k1, $0, _end_ip2_int7
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC4(k0)
		beq		k1, $0, _end_int7_tc4
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#4 割込み終了
_end_int7_tc4:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A70(k0)			# INTCONT クリア
	# INT7(TC#4〜#7) 割込み処理の終了処理
_end_ip2_int7:							# INT7 割込みクリア
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 6)
		sh		k1, 0x0B24(k0)			# io_out16(INTC_INT_PENDING,(1<<6))
	#
	#	INT6(TC#0〜#3) 割込み
	#
_ip2_int6:
		li		k0, 0xB8800000
		lhu		k1, 0x0B24(k0)			# k1=io_in16(INTC_INT_PENDING)
		andi	k1, k1, (1<< 5)
		beq		k1, $0, _ip2_int5
		nop
	# TC#3 割込み
_ip2_int6_tc3:							# TC#3 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A60(k0)			# k1 = io_in16( TC3_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC3 割込み ?
		beq		k1, $0, _ip2_int6_tc2
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC3(k0)
		beq		k1, $0, _end_int6_tc3
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#3 割込み終了
_end_int6_tc3:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A60(k0)			# INTCONT クリア
	# TC#2 割込み
_ip2_int6_tc2:							# TC#2 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A50(k0)			# k1 = io_in16( TC2_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC2 割込み ?
		beq		k1, $0, _ip2_int6_tc1
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC2(k0)
		beq		k1, $0, _end_int6_tc2
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#2 割込み終了
_end_int6_tc2:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A50(k0)			# INTCONT クリア
	# TC#1 割込み
_ip2_int6_tc1:							# TC#1 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A40(k0)			# k1 = io_in16( TC1_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC1 割込み ?
		beq		k1, $0, _ip2_int6_tc0
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC1(k0)
		beq		k1, $0, _end_int6_tc1
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#1 割込み終了
_end_int6_tc1:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A40(k0)			# INTCONT クリア
	# TC#0 割込み
_ip2_int6_tc0:							# TC#0 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0A30(k0)			# k1 = io_in16( TC0_STS );
		andi	k1, k1, (1 << 5)		# INTC_TIMER_TC0 割込み ?
		beq		k1, $0, _end_ip2_int6
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_TC0(k0)
		beq		k1, $0, _end_int6_tc0
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# TC#0 割込み終了
_end_int6_tc0:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)		# k1 = 1 << 5
		sh		k1, 0x0A30(k0)			# INTCONT クリア
	# INT6(TC#0〜#3) 割込み処理の終了処理
_end_ip2_int6:							# INT6 割込みクリア
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 5)
		sh		k1, 0x0B24(k0)			# io_out16(INTC_INT_PENDING,(1<<5))
	#
	#	INT5(CSI, UART1, UART2) 割込み
	#
_ip2_int5:
		li		k0, 0xB8800000
		lhu		k1, 0x0B24(k0)			# k1=io_in16(INTC_INT_PENDING)
		andi	k1, k1, (1<< 4)
		beq		k1, $0, _ret_irq_ip2
		nop
	# CSI 割込み
_ip2_int5_csi:							# CSI 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C92(k0)			# k1 = io_in16( CSI_INTREG );
		andi	k1, k1, (1 << 15)		# CSI送受信完了割込み ?
		beq		k1, $0, _ip2_int5_csi_empty
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_CSI(k0)
		beq		k1, $0, _end_int5_csi
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# CSI 割込み終了
_end_int5_csi:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 15)		# k1 = 1 << 15
		sh		k1, 0x0C92(k0)			# INTCONT クリア
	# CSI 送信エンプティ割込み
_ip2_int5_csi_empty:					# CSI 送信エンプティ割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C92(k0)			# k1 = io_in16( CSI_INTREG );
		andi	k1, k1, (1 << 8)		# CSI 送信エンプティ割込み ?
		beq		k1, $0, _ip2_int5_csi_overflow
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_CSIEMP(k0)
		beq		k1, $0, _end_int5_csiemp
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# CSI 送信エンプティ割込み終了
_end_int5_csiemp:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 8)		# k1 = 1 << 8
		sh		k1, 0x0C92(k0)			# INTCONT クリア
	# CSI 受信オーバーフロー割込み
_ip2_int5_csi_overflow:					# CSI 受信オーバーフロー割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C92(k0)			# k1 = io_in16( CSI_INTREG );
		andi	k1, k1, (1 << 0)		# CSI 受信オーバーフロー割込み ?
		beq		k1, $0, _ip2_int5_csi_overflow
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_CSIOVF(k0)
		beq		k1, $0, _end_int5_csiovf
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# CSI 受信オーバーフロー割込み終了
_end_int5_csiovf:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 0)		# k1 = 1 << 0
		sh		k1, 0x0C92(k0)			# INTCONT クリア
	# UART1 タイムアウト割込み
_ip2_int5_uart1_timeout:				# UART1 タイムアウト割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C04(k0)			# k1 = io_in16( UART_1IIR );
		andi	k1, k1, (1 << 3)		# UART1 タイムアウト割込み ?
		beq		k1, $0, _ip2_int5_uart1
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART1TO(k0)
		beq		k1, $0, _end_int5_uart1to
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART1 タイムアウト割込み終了
_end_int5_uart1to:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 3)		# k1 = 1 << 3
		sh		k1, 0x0C04(k0)			# INTCONT クリア
	# UART1 割込み
_ip2_int5_uart1:						# UART1 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C04(k0)			# k1 = io_in16( UART_1IIR );
		andi	k1, k1, (1 << 0)		# UART1 割込み ?
		beq		k1, $0, _ip2_int5_uart1
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART1(k0)
		beq		k1, $0, _end_int5_uart1
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART1 割込み終了
_end_int5_uart1:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 0)		# k1 = 1 << 0
		sh		k1, 0x0C04(k0)			# INTCONT クリア
	# UART2 タイムアウト割込み
_ip2_int5_uart2_timeout:				# UART2 タイムアウト割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C44(k0)			# k1 = io_in16( UART_2IIR );
		andi	k1, k1, (1 << 3)		# UART2 タイムアウト割込み ?
		beq		k1, $0, _ip2_int5_uart2
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART2TO(k0)
		beq		k1, $0, _end_int5_uart2to
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART2 タイムアウト割込み終了
_end_int5_uart2to:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 3)		# k1 = 1 << 3
		sh		k1, 0x0C44(k0)			# INTCONT クリア
	# UART2 割込み
_ip2_int5_uart2:						# UART2 割込み確認
		li		k0, 0xB8800000
		lhu		k1, 0x0C44(k0)			# k1 = io_in16( UART_2IIR );
		andi	k1, k1, (1 << 0)		# UART2 割込み ?
		beq		k1, $0, _end_ip2_int5
		nop
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_UART2(k0)
		beq		k1, $0, _end_int5_uart2
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# UART2 割込み終了
_end_int5_uart2:
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 0)		# k1 = 1 << 0
		sh		k1, 0x0C44(k0)			# INTCONT クリア
	# INT5(CSI,UART1,UART2) 割込み処理の終了処理
_end_ip2_int5:							# INT5 割込みクリア
		li		k0, 0xB8800000
		ori		k1, $0, (1 << 4)
		sh		k1, 0x0B24(k0)			# io_out16(INTC_INT_PENDING,(1<<4))
	# IP2 割込み処理の終了処理
_ret_irq_ip2:
	# レジスタ復帰後 eret へ
		li		k0, 0xB8800000
		beql	$0, $0, _ret_from_irq
		nop
#
#	IP1 例外処理 (ソフトウェア割込み１)
#
_irq_ip1:
		li		k0, 0x80000000
		lw		k1, HOS_VA_IP1(k0)
		beql	k1, $0, _ret_from_irq	# 処理していない場合はそのまま復帰
		nop
		jal		k1
		nop
	# レジスタ復帰後 eret へ
		beql	$0, $0, _ret_from_irq
		nop
#
#	IP0 例外処理 (ソフトウェア割込み０)
#
_irq_ip0:
		li		k0, 0x80000000
		lw		k1, HOS_VA_IP0(k0)
		beql	k1, $0, _ret_from_irq	# 処理していない場合はそのまま復帰
		nop
		jal		k1
		nop
	# レジスタ復帰後 eret へ
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 1 例外処理
#		1 	Mod 	TLB変更例外
#
_exccode_1:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode1(k0)
		beq		k1, $0, _end_exccode_1
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_1:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 2 例外処理
#		2 	TLBL 	TLB不一致例外（ロードまたは命令フェッチ)
#
_exccode_2:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode2(k0)
		beq		k1, $0, _end_exccode_2
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_2:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 3 例外処理
#		3 	TLBS 	TLB不一致例外（ストア）
#
_exccode_3:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode3(k0)
		beq		k1, $0, _end_exccode_3
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_3:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 4 例外処理
#		4 	AdEL 	アドレス・エラー例外（ロードまたは命令フェッチ）
#
_exccode_4:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode4(k0)
		beq		k1, $0, _end_exccode_4
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_4:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 5 例外処理
#		5 	AdES 	アドレス・エラー例外（ストア）
#
_exccode_5:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode5(k0)
		beq		k1, $0, _end_exccode_5
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_5:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 6 例外処理
#		6 	IBE 	バス・エラー例外（命令フェッチ）
#
#_exccode_6:
#	# ベクタ番号から呼び出し先アドレスを取得
#
#	# ExcCode 6 終了
#	# レジスタ復帰後 eret へ
#		beql	$0, $0, _ret_from_irq
#		nop
#
#	ExcCode 7 例外処理
#		7 	DBE 	バス・エラー例外（データのロードまたはストア）
#
#_exccode_7:
#	# ベクタ番号から呼び出し先アドレスを取得
#
#	# ExcCode 7 終了
#	# レジスタ復帰後 eret へ
#		beql	$0, $0, _ret_from_irq
#		nop
#
#	ExcCode 8 例外処理
#		8 	Sys 	システム・コール例外
#
_exccode_8:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode8(k0)
		beq		k1, $0, _end_exccode_8
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_8:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 9 例外処理
#		9 	Bp		ブレークポイント例外
#
_exccode_9:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode8(k0)
		beq		k1, $0, _end_exccode_8
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_9:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 10 例外処理
#		10 	RI		予約命令例外
#
_exccode_10:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode10(k0)
		beq		k1, $0, _end_exccode_10
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_10:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 11 例外処理
#		11 	CpU		コプロセッサ使用不可例外
#
_exccode_11:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode11(k0)
		beq		k1, $0, _end_exccode_11
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_11:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 12 例外処理
#		12 	Ov		演算オーバフロー例外
#
_exccode_12:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode11(k0)
		beq		k1, $0, _end_exccode_11
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_12:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 13 例外処理
#		13 	Tr		トラップ例外
#
_exccode_13:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode11(k0)
		beq		k1, $0, _end_exccode_11
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_13:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 15 例外処理
#		15 	FPE 	浮動小数点例外
#
_exccode_15:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode11(k0)
		beq		k1, $0, _end_exccode_11
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_15:
		beql	$0, $0, _ret_from_irq
		nop
#
#	ExcCode 23 例外処理
#		23 	Watch 	ウォッチ例外
#
_exccode_23:
	# ベクタ番号から呼び出し先アドレスを取得
		li		k0, 0x80000000
		lw		k1, HOS_VA_ExcCode23(k0)
		beq		k1, $0, _end_exccode_23
		nop
		jal		k1						# 指定アドレスを呼び出す
		nop
	# レジスタ復帰後 eret へ
_end_exccode_23:
		beql	$0, $0, _ret_from_irq
		nop
#
# レジスタ復帰処理と eret
#
_ret_from_irq:
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
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
