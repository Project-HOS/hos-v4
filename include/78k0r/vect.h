/****************************************************************************/
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*      78K0R用例外処理（割込み）定義                                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2009 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/****************************************************************************/
#ifndef	__HOSv4_78K0R_vect_h__
#define	__HOSv4_78K0R_vect_h__

#define	HOS_VN_INTWDTI			(0)
#define	HOS_VN_INTLVI			(1)
#define	HOS_VN_INTP0			(2)
#define	HOS_VN_INTP1			(3)
#define	HOS_VN_INTP2			(4)
#define	HOS_VN_INTP3			(5)
#define	HOS_VN_INTP4			(6)
#define	HOS_VN_INTP5			(7)
#define	HOS_VN_INTST3			(8)
#define	HOS_VN_INTSR3			(9)
#define	HOS_VN_INTSRE3			(10)
#define	HOS_VN_INTDMA0			(11)
#define	HOS_VN_INTDMA1			(12)
#define	HOS_VN_INTST0			(13)
#define	HOS_VN_INTSR0			(14)
#define	HOS_VN_INTSRE0			(15)
#define	HOS_VN_INTST1			(16)
#define	HOS_VN_INTSR1			(17)
#define	HOS_VN_INTSRE1			(18)
#define	HOS_VN_INTIIC0			(19)
#define	HOS_VN_INTTM00			(20)
#define	HOS_VN_INTTM01			(21)
#define	HOS_VN_INTTM02			(22)
#define	HOS_VN_INTTM03			(23)
#define	HOS_VN_INTAD			(24)
#define	HOS_VN_INTRTC			(25)
#define	HOS_VN_INTRTCI			(26)
#define	HOS_VN_INTKR			(27)
#define	HOS_VN_INTST2			(28)
#define	HOS_VN_INTSR2			(29)
#define	HOS_VN_INTSRE2			(30)
#define	HOS_VN_INTTM04			(31)
#define	HOS_VN_INTTM05			(32)
#define	HOS_VN_INTTM06			(33)
#define	HOS_VN_INTTM07			(34)
#define	HOS_VN_INTP6			(35)
#define	HOS_VN_INTP7			(36)
#define	HOS_VN_INTP8			(37)
#define	HOS_VN_INTP9			(38)
#define	HOS_VN_INTP10			(39)
#define	HOS_VN_INTP11			(40)

#define	HOS_VN_INTCSI00			HOS_VN_INTST0
#define	HOS_VN_INTCSI01			HOS_VN_INTSR0
#define	HOS_VN_INTCSI10			HOS_VN_INTST1
#define	HOS_VN_INTIIC10			HOS_VN_INTST1
#define	HOS_VN_INTCSI20			HOS_VN_INTST2
#define	HOS_VN_INTIIC20			HOS_VN_INTST2

#endif	/* __HOSv4_78K0R_vect_h__ */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2009 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
