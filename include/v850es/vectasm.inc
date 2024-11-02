#	************************************************************************
#		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
#			例外処理（割込み）定義
#									Copyright (C) 1998-2008 by Project HOS
#									http://sourceforge.jp/projects/hos/
#	************************************************************************

	.set	HOS_VN_INTLVI,		8
	.set	HOS_VN_INTP0,		9
	.set	HOS_VN_INTP1,		10
	.set	HOS_VN_INTP2,		11
	.set	HOS_VN_INTP3,		12
	.set	HOS_VN_INTP4,		13
	.set	HOS_VN_INTP5,		14
	.set	HOS_VN_INTP6,		15
	.set	HOS_VN_INTP7,		16
	.set	HOS_VN_INTTQ0OV,	17
	.set	HOS_VN_INTTQ0CC0,	18
	.set	HOS_VN_INTTQ0CC1,	19
	.set	HOS_VN_INTTQ0CC2,	20
	.set	HOS_VN_INTTQ0CC3,	21
	.set	HOS_VN_INTTP0OV,	22
	.set	HOS_VN_INTTP0CC0,	23
	.set	HOS_VN_INTTP0CC1,	24
	.set	HOS_VN_INTTP1OV,	25
	.set	HOS_VN_INTTP1CC0,	26
	.set	HOS_VN_INTTP1CC1,	27
	.set	HOS_VN_INTTP2OV,	28
	.set	HOS_VN_INTTP2CC0,	29
	.set	HOS_VN_INTTP2CC1,	30
	.set	HOS_VN_INTTP3OV,	31
	.set	HOS_VN_INTTP3CC0,	32
	.set	HOS_VN_INTTP3CC1,	33
	.set	HOS_VN_INTTP4OV,	34
	.set	HOS_VN_INTTP4CC0,	35
	.set	HOS_VN_INTTP4CC1,	36
	.set	HOS_VN_INTTP5OV,	37
	.set	HOS_VN_INTTP5CC0,	38
	.set	HOS_VN_INTTP5CC1,	39
	.set	HOS_VN_INTTM0EQ0,	40	-- HOS OSTimer
	.set	HOS_VN_INTCB0R,		41
	.set	HOS_VN_INTCB0T,		42
	.set	HOS_VN_INTCB1R,		43
	.set	HOS_VN_INTCB1T,		44
	.set	HOS_VN_INTCB2R,		45
	.set	HOS_VN_INTCB2T,		46
	.set	HOS_VN_INTCB3R,		47
	.set	HOS_VN_INTCB3T,		48
	.set	HOS_VN_INTCB4R,		49
	.set	HOS_VN_INTCB4T,		50
	.set	HOS_VN_INTUA1R,		51
	.set	HOS_VN_INTUA1T,		52
	.set	HOS_VN_INTUA2R,		53
	.set	HOS_VN_INTUA2T,		54
	.set	HOS_VN_INTAD,		55
	.set	HOS_VN_INTDMA0,		56
	.set	HOS_VN_INTDMA1,		57
	.set	HOS_VN_INTDMA2,		58
	.set	HOS_VN_INTDMA3,		59
	.set	HOS_VN_INTKR,		60
	.set	HOS_VN_INTWTI,		61
	.set	HOS_VN_INTWT,		62
	.set	HOS_VN_MAXINTNO,	63

	.set	HOS_VN_INTUA0R,		HOS_VN_INTCB4R
	.set	HOS_VN_INTUA0T,		HOS_VN_INTCB4T
	.set	HOS_VN_INTIIC0,		HOS_VN_INTUA2R
	.set	HOS_VN_INTIIC2,		HOS_VN_INTUA1R
	.set	HOS_VN_INTIIC1,		HOS_VN_INTCB0R

#	-----------------------------------------------------------------------
#		Copyright (C) 1998-2008 by Project HOS
#	-----------------------------------------------------------------------
