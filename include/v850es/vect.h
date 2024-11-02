/****************************************************************************/
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*      例外処理（割込み）定義                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/****************************************************************************/
#ifndef	__HOSv4_V850ES_vect_h__
#define	__HOSv4_V850ES_vect_h__

#define	HOS_VN_INTLVI		(8)
#define	HOS_VN_INTP0		(9)
#define	HOS_VN_INTP1		(10)
#define	HOS_VN_INTP2		(11)
#define	HOS_VN_INTP3		(12)
#define	HOS_VN_INTP4		(13)
#define	HOS_VN_INTP5		(14)
#define	HOS_VN_INTP6		(15)
#define	HOS_VN_INTP7		(16)
#define	HOS_VN_INTTQ0OV		(17)
#define	HOS_VN_INTTQ0CC0	(18)
#define	HOS_VN_INTTQ0CC1	(19)
#define	HOS_VN_INTTQ0CC2	(20)
#define	HOS_VN_INTTQ0CC3	(21)
#define	HOS_VN_INTTP0OV		(22)
#define	HOS_VN_INTTP0CC0	(23)
#define	HOS_VN_INTTP0CC1	(24)
#define	HOS_VN_INTTP1OV		(25)
#define	HOS_VN_INTTP1CC0	(26)
#define	HOS_VN_INTTP1CC1	(27)
#define	HOS_VN_INTTP2OV		(28)
#define	HOS_VN_INTTP2CC0	(29)
#define	HOS_VN_INTTP2CC1	(30)
#define	HOS_VN_INTTP3OV		(31)
#define	HOS_VN_INTTP3CC0	(32)
#define	HOS_VN_INTTP3CC1	(33)
#define	HOS_VN_INTTP4OV		(34)
#define	HOS_VN_INTTP4CC0	(35)
#define	HOS_VN_INTTP4CC1	(36)
#define	HOS_VN_INTTP5OV		(37)
#define	HOS_VN_INTTP5CC0	(38)
#define	HOS_VN_INTTP5CC1	(39)
#define	HOS_VN_INTTM0EQ0	(40)	// HOS OSTimer
#define	HOS_VN_INTCB0R		(41)
#define	HOS_VN_INTCB0T		(42)
#define	HOS_VN_INTCB1R		(43)
#define	HOS_VN_INTCB1T		(44)
#define	HOS_VN_INTCB2R		(45)
#define	HOS_VN_INTCB2T		(46)
#define	HOS_VN_INTCB3R		(47)
#define	HOS_VN_INTCB3T		(48)
#define	HOS_VN_INTCB4R		(49)
#define	HOS_VN_INTCB4T		(50)
#define	HOS_VN_INTUA1R		(51)
#define	HOS_VN_INTUA1T		(52)
#define	HOS_VN_INTUA2R		(53)
#define	HOS_VN_INTUA2T		(54)
#define	HOS_VN_INTAD		(55)
#define	HOS_VN_INTDMA0		(56)
#define	HOS_VN_INTDMA1		(57)
#define	HOS_VN_INTDMA2		(58)
#define	HOS_VN_INTDMA3		(59)
#define	HOS_VN_INTKR		(60)
#define	HOS_VN_INTWTI		(61)
#define	HOS_VN_INTWT		(62)
#define	HOS_VN_MAXINTNO		(63)

#define	HOS_VN_INTUA0R		(HOS_VN_INTCB4R)
#define	HOS_VN_INTUA0T		(HOS_VN_INTCB4T)
#define	HOS_VN_INTIIC0		(HOS_VN_INTUA2R)
#define	HOS_VN_INTIIC2		(HOS_VN_INTUA1R)
#define	HOS_VN_INTIIC1		(HOS_VN_INTCB0R)

#endif	/* __HOSv4_V850ES_vect_h__ */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
