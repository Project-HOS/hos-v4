/****************************************************************************/
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*      例外処理（割込み）定義                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/****************************************************************************/
#ifndef	__vect_h__
#define	__vect_h__

#define	HOS_VN_ExcCode0		(5)
#define	HOS_VN_ExcCode1		(6)
#define	HOS_VN_ExcCode2		(7)
#define	HOS_VN_ExcCode3		(8)
#define	HOS_VN_ExcCode4		(9)
#define	HOS_VN_ExcCode5		(10)
#define	HOS_VN_ExcCode6		(11)
#define	HOS_VN_ExcCode7		(12)
#define	HOS_VN_ExcCode8		(13)
#define	HOS_VN_ExcCode9		(14)
#define	HOS_VN_ExcCode10	(15)
#define	HOS_VN_ExcCode11	(16)
#define	HOS_VN_ExcCode12	(17)
#define	HOS_VN_ExcCode13	(18)
#define	HOS_VN_ExcCode14	(19)
#define	HOS_VN_ExcCode15	(20)
#define	HOS_VN_ExcCode16	(21)
#define	HOS_VN_ExcCode17	(22)
#define	HOS_VN_ExcCode18	(23)
#define	HOS_VN_ExcCode19	(24)
#define	HOS_VN_ExcCode20	(25)
#define	HOS_VN_ExcCode21	(26)
#define	HOS_VN_ExcCode22	(27)
#define	HOS_VN_ExcCode23	(28)
#define	HOS_VN_ExcCode24	(29)
#define	HOS_VN_ExcCode25	(30)
#define	HOS_VN_ExcCode26	(31)
#define	HOS_VN_ExcCode27	(32)
#define	HOS_VN_ExcCode28	(33)
#define	HOS_VN_ExcCode29	(34)
#define	HOS_VN_ExcCode30	(35)
#define	HOS_VN_ExcCode31	(36)
#define	HOS_VN_IP7			(37)
#define	HOS_VN_IP6			(38)
#define	HOS_VN_IP5			(39)
#define	HOS_VN_IP4			(40)
#define	HOS_VN_IP3			(41)
#define	HOS_VN_IP2			(42)
#define	HOS_VN_IP1			(43)
#define	HOS_VN_IP0			(44)
#define	HOS_VN_SYSCALL		(45)
/* VR9721, UX1200E */
#define	HOS_VN_TC7			(64)
#define	HOS_VN_TC6			(65)
#define	HOS_VN_TC5			(66)
#define	HOS_VN_TC4			(67)
#define	HOS_VN_TC3			(68)
#define	HOS_VN_TC2			(69)
#define	HOS_VN_TC1			(70)
#define	HOS_VN_TC0			(71)
#define	HOS_VN_CSI			(72)
#define	HOS_VN_CSIEMP		(73)
#define	HOS_VN_CSIOVF		(74)
#define	HOS_VN_UART1TO		(75)
#define	HOS_VN_UART1		(76)
#define	HOS_VN_UART2TO		(77)
#define	HOS_VN_UART2		(78)
/* SEMB1200A */
#define	HOS_VN_PWM0			(112)
#define	HOS_VN_PWM1			(113)
#define	HOS_VN_PWM2			(114)
#define	HOS_VN_PWM3			(115)
#define	HOS_VN_UART30		(116)
#define	HOS_VN_UART31		(117)
#define	HOS_VN_UART32		(118)
#define	HOS_VN_UART33		(119)
#define	HOS_VN_UART34		(120)
#define	HOS_VN_UART35		(121)
#define	HOS_VN_UART36		(122)
#define	HOS_VN_UART37		(123)

#endif
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
