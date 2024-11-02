;	------------------------------------------------------------------------
;		Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
;			プロセッサ抽象化コンポーネント (78K0Rコア用)
;
;									Copyright (C) 1998-2009 by Project HOS
;									http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;		$ PROCESSOR	(F1166A0)				; ra78k0r 起動オプションで指定
		$ INCLUDE	(78k0r/vectasm.inc)		; 割込みベクタ番号定義
;	************************************************************************
;		割込みベクタの設定
;			saddrs intno に割込み番号を代入し、int_handler()関数へジャンプする
;			割込み番号は include/78k0r/vectasm.inc と vect.h で定義（同一）
;	************************************************************************
		DSEG	SADDRP
		EXTRN	intno

		CSEG	BASE
		EXTRN	_int_handler

_int_INTWDTI:
		movw	intno, #HOS_VN_INTWDTI
		br		!!_int_handler
_int_INTLVI:
		movw	intno, #HOS_VN_INTLVI
		br		!!_int_handler
_int_INTP0:
		movw	intno, #HOS_VN_INTP0
		br		!!_int_handler
_int_INTP1:
		movw	intno, #HOS_VN_INTP1
		br		!!_int_handler
_int_INTP2:
		movw	intno, #HOS_VN_INTP2
		br		!!_int_handler
_int_INTP3:
		movw	intno, #HOS_VN_INTP3
		br		!!_int_handler
_int_INTP4:
		movw	intno, #HOS_VN_INTP4
		br		!!_int_handler
_int_INTP5:
		movw	intno, #HOS_VN_INTP5
		br		!!_int_handler
_int_INTST3:
		movw	intno, #HOS_VN_INTST3
		br		!!_int_handler
_int_INTSR3:
		movw	intno, #HOS_VN_INTSR3
		br		!!_int_handler
_int_INTSRE3:
		movw	intno, #HOS_VN_INTSRE3
		br		!!_int_handler
_int_INTDMA0:
		movw	intno, #HOS_VN_INTDMA0
		br		!!_int_handler
_int_INTDMA1:
		movw	intno, #HOS_VN_INTDMA1
		br		!!_int_handler
_int_INTST0:
		movw	intno, #HOS_VN_INTST0
		br		!!_int_handler
_int_INTSR0:
		movw	intno, #HOS_VN_INTSR0
		br		!!_int_handler
_int_INTSRE0:
		movw	intno, #HOS_VN_INTSRE0
		br		!!_int_handler
_int_INTST1:
		movw	intno, #HOS_VN_INTST1
		br		!!_int_handler
_int_INTSR1:
		movw	intno, #HOS_VN_INTSR1
		br		!!_int_handler
_int_INTSRE1:
		movw	intno, #HOS_VN_INTSRE1
		br		!!_int_handler
_int_INTIIC0:
		movw	intno, #HOS_VN_INTIIC0
		br		!!_int_handler
_int_INTTM00:
		movw	intno, #HOS_VN_INTTM00
		br		!!_int_handler
_int_INTTM01:
		movw	intno, #HOS_VN_INTTM01
		br		!!_int_handler
_int_INTTM02:
		movw	intno, #HOS_VN_INTTM02
		br		!!_int_handler
_int_INTTM03:
		movw	intno, #HOS_VN_INTTM03
		br		!!_int_handler
_int_INTAD:
		movw	intno, #HOS_VN_INTAD
		br		!!_int_handler
_int_INTRTC:
		movw	intno, #HOS_VN_INTRTC
		br		!!_int_handler
_int_INTRTCI:
		movw	intno, #HOS_VN_INTRTCI
		br		!!_int_handler
_int_INTKR:
		movw	intno, #HOS_VN_INTKR
		br		!!_int_handler
_int_INTST2:
		movw	intno, #HOS_VN_INTST2
		br		!!_int_handler
_int_INTSR2:
		movw	intno, #HOS_VN_INTSR2
		br		!!_int_handler
_int_INTSRE2:
		movw	intno, #HOS_VN_INTSRE2
		br		!!_int_handler
_int_INTTM04:
		movw	intno, #HOS_VN_INTTM04
		br		!!_int_handler
_int_INTTM05:
		movw	intno, #HOS_VN_INTTM05
		br		!!_int_handler
_int_INTTM06:
		movw	intno, #HOS_VN_INTTM06
		br		!!_int_handler
_int_INTTM07:
		movw	intno, #HOS_VN_INTTM07
		br		!!_int_handler
_int_INTP6:
		movw	intno, #HOS_VN_INTP6
		br		!!_int_handler
_int_INTP7:
		movw	intno, #HOS_VN_INTP7
		br		!!_int_handler
_int_INTP8:
		movw	intno, #HOS_VN_INTP8
		br		!!_int_handler
_int_INTP9:
		movw	intno, #HOS_VN_INTP9
		br		!!_int_handler
_int_INTP10:
		movw	intno, #HOS_VN_INTP10
		br		!!_int_handler
_int_INTP11:
		movw	intno, #HOS_VN_INTP11
		br		!!_int_handler

@@VECT04	CSEG	AT 0004H
		DW		_int_INTWDTI
@@VECT06	CSEG	AT 0006H
		DW		_int_INTLVI
@@VECT08	CSEG	AT 0008H
		DW		_int_INTP0
@@VECT0A	CSEG	AT 000AH
		DW		_int_INTP1
@@VECT0C	CSEG	AT 000CH
		DW		_int_INTP2
@@VECT0E	CSEG	AT 000EH
		DW		_int_INTP3
@@VECT10	CSEG	AT 0010H
		DW		_int_INTP4
@@VECT12	CSEG	AT 0012H
		DW		_int_INTP5
@@VECT14	CSEG	AT 0014H
		DW		_int_INTST3
@@VECT16	CSEG	AT 0016H
		DW		_int_INTSR3
@@VECT18	CSEG	AT 0018H
		DW		_int_INTSRE3
@@VECT1A	CSEG	AT 001AH
		DW		_int_INTDMA0
@@VECT1C	CSEG	AT 001CH
		DW		_int_INTDMA1
@@VECT1E	CSEG	AT 001EH
		DW		_int_INTST0
@@VECT20	CSEG	AT 0020H
		DW		_int_INTSR0
@@VECT22	CSEG	AT 0022H
		DW		_int_INTSRE0
@@VECT24	CSEG	AT 0024H
		DW		_int_INTST1
@@VECT26	CSEG	AT 0026H
		DW		_int_INTSR1
@@VECT28	CSEG	AT 0028H
		DW		_int_INTSRE1
@@VECT2A	CSEG	AT 002AH
		DW		_int_INTIIC0
@@VECT2C	CSEG	AT 002CH
		DW		_int_INTTM00
@@VECT2E	CSEG	AT 002EH
		DW		_int_INTTM01
@@VECT30	CSEG	AT 0030H
		DW		_int_INTTM02
@@VECT32	CSEG	AT 0032H
		DW		_int_INTTM03
@@VECT34	CSEG	AT 0034H
		DW		_int_INTAD
@@VECT36	CSEG	AT 0036H
		DW		_int_INTRTC
@@VECT38	CSEG	AT 0038H
		DW		_int_INTRTCI
@@VECT3A	CSEG	AT 003AH
		DW		_int_INTKR
@@VECT3C	CSEG	AT 003CH
		DW		_int_INTST2
@@VECT3E	CSEG	AT 003EH
		DW		_int_INTSR2
@@VECT40	CSEG	AT 0040H
		DW		_int_INTSRE2
@@VECT42	CSEG	AT 0042H
		DW		_int_INTTM04
@@VECT44	CSEG	AT 0044H
		DW		_int_INTTM05
@@VECT46	CSEG	AT 0046H
		DW		_int_INTTM06
@@VECT48	CSEG	AT 0048H
		DW		_int_INTTM07
@@VECT4A	CSEG	AT 004AH
		DW		_int_INTP6
@@VECT4C	CSEG	AT 004CH
		DW		_int_INTP7
@@VECT4E	CSEG	AT 004EH
		DW		_int_INTP8
@@VECT50	CSEG	AT 0050H
		DW		_int_INTP9
@@VECT52	CSEG	AT 0052H
		DW		_int_INTP10
@@VECT54	CSEG	AT 0054H
		DW		_int_INTP11
			CSEG	BASE
		END
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
