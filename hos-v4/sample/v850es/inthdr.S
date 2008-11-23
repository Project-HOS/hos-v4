#	------------------------------------------------------------------------
#		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
#			プロセッサ抽象化コンポーネント (V850ES互換コア用)
#
#									Copyright (C) 1998-2008 by Project HOS
#									http://sourceforge.jp/projects/hos/
#	------------------------------------------------------------------------
#		.option		cpu F3716				-- as850 起動オプションで指定
		.include	"v850es/vectasm.inc"	-- 割込みベクタ番号定義
#	************************************************************************
#		割込みベクタの設定
#			r2 レジスタに割込み番号を代入し、int_handler()関数へジャンプする
#			割込み番号は include/v850es/vectasm.inc と vect.h で定義（同一）
#	************************************************************************
	.text
	.section	"INTLVI"
		mov		HOS_VN_INTLVI, r2		-- 8
		jr		_int_handler
	.section	"INTP0"
		mov		HOS_VN_INTP0, r2		-- 9
		jr		_int_handler
	.section	"INTP1"
		mov		HOS_VN_INTP1, r2		-- 10
		jr		_int_handler
	.section	"INTP2"
		mov		HOS_VN_INTP2, r2		-- 11
		jr		_int_handler
	.section	"INTP3"
		mov		HOS_VN_INTP3, r2		-- 12
		jr		_int_handler
	.section	"INTP4"
		mov		HOS_VN_INTP4, r2		-- 13
		jr		_int_handler
	.section	"INTP5"
		mov		HOS_VN_INTP5, r2		-- 14
		jr		_int_handler
	.section	"INTP6"
		mov		HOS_VN_INTP6, r2		-- 15
		jr		_int_handler
	.section	"INTP7"
		mov		HOS_VN_INTP7, r2		-- 16
		jr		_int_handler
	.section	"INTTQ0OV"
		mov		HOS_VN_INTTQ0OV, r2		-- 17
		jr		_int_handler
	.section	"INTTQ0CC0"
		mov		HOS_VN_INTTQ0CC0, r2	-- 18
		jr		_int_handler
	.section	"INTTQ0CC1"
		mov		HOS_VN_INTTQ0CC1, r2	-- 19
		jr		_int_handler
	.section	"INTTQ0CC2"
		mov		HOS_VN_INTTQ0CC2, r2	-- 20
		jr		_int_handler
	.section	"INTTQ0CC3"
		mov		HOS_VN_INTTQ0CC3, r2	-- 21
		jr		_int_handler
	.section	"INTTP0OV"
		mov		HOS_VN_INTTP0OV, r2		-- 22
		jr		_int_handler
	.section	"INTTP0CC0"
		mov		HOS_VN_INTTP0CC0, r2	-- 23
		jr		_int_handler
	.section	"INTTP0CC1"
		mov		HOS_VN_INTTP0CC1, r2	-- 24
		jr		_int_handler
	.section	"INTTP1OV"
		mov		HOS_VN_INTTP1OV, r2		-- 25
		jr		_int_handler
	.section	"INTTP1CC0"
		mov		HOS_VN_INTTP1CC0, r2	-- 26
		jr		_int_handler
	.section	"INTTP1CC1"
		mov		HOS_VN_INTTP1CC1, r2	-- 27
		jr		_int_handler
	.section	"INTTP2OV"
		mov		HOS_VN_INTTP2OV, r2		-- 28
		jr		_int_handler
	.section	"INTTP2CC0"
		mov		HOS_VN_INTTP2CC0, r2	-- 29
		jr		_int_handler
	.section	"INTTP2CC1"
		mov		HOS_VN_INTTP2CC1, r2	-- 30
		jr		_int_handler
	.section	"INTTP3OV"
		mov		HOS_VN_INTTP3OV, r2		-- 31
		jr		_int_handler
	.section	"INTTP3CC0"
		mov		HOS_VN_INTTP3CC0, r2	-- 32
		jr		_int_handler
	.section	"INTTP3CC1"
		mov		HOS_VN_INTTP3CC1, r2	-- 33
		jr		_int_handler
	.section	"INTTP4OV"
		mov		HOS_VN_INTTP4OV, r2		-- 34
		jr		_int_handler
	.section	"INTTP4CC0"
		mov		HOS_VN_INTTP4CC0, r2	-- 35
		jr		_int_handler
	.section	"INTTP4CC1"
		mov		HOS_VN_INTTP4CC1, r2	-- 36
		jr		_int_handler
	.section	"INTTP5OV"
		mov		HOS_VN_INTTP5OV, r2		-- 37
		jr		_int_handler
	.section	"INTTP5CC0"
		mov		HOS_VN_INTTP5CC0, r2	-- 38
		jr		_int_handler
	.section	"INTTP5CC1"
		mov		HOS_VN_INTTP5CC1, r2	-- 39
		jr		_int_handler
	.section	"INTTM0EQ0"
		mov		HOS_VN_INTTM0EQ0, r2	-- 40	-- HOS OSTimer
		jr		_int_handler
	.section	"INTCB0R"
		mov		HOS_VN_INTCB0R, r2		-- 41
		jr		_int_handler
	.section	"INTCB0T"
		mov		HOS_VN_INTCB0T, r2		-- 42
		jr		_int_handler
	.section	"INTCB1R"
		mov		HOS_VN_INTCB1R, r2		-- 43
		jr		_int_handler
	.section	"INTCB1T"
		mov		HOS_VN_INTCB1T, r2		-- 44
		jr		_int_handler
	.section	"INTCB2R"
		mov		HOS_VN_INTCB2R, r2		-- 45
		jr		_int_handler
	.section	"INTCB2T"
		mov		HOS_VN_INTCB2T, r2		-- 46
		jr		_int_handler
	.section	"INTCB3R"
		mov		HOS_VN_INTCB3R, r2		-- 47
		jr		_int_handler
	.section	"INTCB3T"
		mov		HOS_VN_INTCB3T, r2		-- 48
		jr		_int_handler
	.section	"INTCB4R"
		mov		HOS_VN_INTCB4R, r2		-- 49
		jr		_int_handler
	.section	"INTCB4T"
		mov		HOS_VN_INTCB4T, r2		-- 50
		jr		_int_handler
	.section	"INTUA1R"
		mov		HOS_VN_INTUA1R, r2		-- 51
		jr		_int_handler
	.section	"INTUA1T"
		mov		HOS_VN_INTUA1T, r2		-- 52
		jr		_int_handler
	.section	"INTUA2R"
		mov		HOS_VN_INTUA2R, r2		-- 53
		jr		_int_handler
	.section	"INTUA2T"
		mov		HOS_VN_INTUA2T, r2		-- 54
		jr		_int_handler
	.section	"INTAD"
		mov		HOS_VN_INTAD, r2		-- 55
		jr		_int_handler
	.section	"INTDMA0"
		mov		HOS_VN_INTDMA0, r2		-- 56
		jr		_int_handler
	.section	"INTDMA1"
		mov		HOS_VN_INTDMA1, r2		-- 57
		jr		_int_handler
	.section	"INTDMA2"
		mov		HOS_VN_INTDMA2, r2		-- 58
		jr		_int_handler
	.section	"INTDMA3"
		mov		HOS_VN_INTDMA3, r2		-- 59
		jr		_int_handler
	.section	"INTKR"
		mov		HOS_VN_INTKR, r2		-- 60
		jr		_int_handler
	.section	"INTWTI"
		mov		HOS_VN_INTWTI, r2		-- 61
		jr		_int_handler
	.section	"INTWT"
		mov		HOS_VN_INTWT, r2		-- 62
		jr		_int_handler
	.previous
#	------------------------------------------------------------------------
#		Copyright (C) 1998-2008 by Project HOS
#	------------------------------------------------------------------------

