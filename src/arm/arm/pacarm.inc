; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                     
;    アセンブリ言語共通インクルードファイル                                   
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


; フラグ定義
Mode_USR		EQU 	0x10		; USR モード
Mode_FIQ		EQU		0x11		; FIQ モード
Mode_IRQ		EQU 	0x12		; IRQ モード
Mode_SVR		EQU		0x13		; Supervisor モード
Mode_ABT		EQU		0x17		; Abort モード
Mode_UND		EQU		0x1b		; Undefined モード
Mode_SYS		EQU 	0x1f		; System モード

T_Bit			EQU		0x20		; T ビット
F_Bit			EQU 	0x40		; F ビット
I_Bit			EQU 	0x80		; I ビット


; CPU例外ハンドラ番号定義
EXCNO_UND		EQU		1			; Undefined例外
EXCNO_SWI		EQU		2			; SWI例外
EXCNO_PRE		EQU		3			; プリフェッチアボート
EXCNO_DAT		EQU		4			; データアボート


				END


; ---------------------------------------------------------------------------
;  Copyright (C) 1998-2002 by Project HOS                                    
; ---------------------------------------------------------------------------
