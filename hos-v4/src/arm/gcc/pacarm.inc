/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (ARM gcc用)                            */
/*   アセンブリ言語共通インクルードファイル                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



				/* フラグ定義 */
				.equ	Mode_USR, 0x10		/* USR モード */
				.equ	Mode_FIQ, 0x11		/* FIQ モード */
				.equ	Mode_IRQ, 0x12		/* IRQ モード */
				.equ	Mode_SVR, 0x13		/* Supervisor モード */
				.equ	Mode_ABT, 0x17		/* Abort モード */
				.equ	Mode_UND, 0x1b		/* Undefined モード */
				.equ	Mode_SYS, 0x1f		/* System モード */

				.equ	T_Bit, 0x20			/* T ビット */
				.equ	F_Bit, 0x40			/* F ビット */
				.equ	I_Bit, 0x80			/* I ビット */


				/* CPU例外ハンドラ番号定義 */
				.equ	EXCNO_UND, 1		/* Undefined例外 */
				.equ	EXCNO_SWI, 2		/* SWI例外 */
				.equ	EXCNO_PRE, 3		/* プリフェッチアボート */
				.equ	EXCNO_DAT, 4		/* データアボート */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
