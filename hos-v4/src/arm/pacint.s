; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    例外ハンドラ                                                            
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------


; 定数定義
Mode_USR		EQU 	0x10
Mode_IRQ		EQU 	0x12

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40


				AREA	inthdr_code, CODE, READONLY

				EXPORT	_HOS_UndefinedHandler
				EXPORT  _HOS_SwiHandler
				EXPORT	_HOS_PrefetchHandler
				EXPORT	_HOS_AbortHandler


; ----------------------------------------------
;  Undefined ハンドラ
; ----------------------------------------------
_HOS_UndefinedHandler
				b		_HOS_UndefinedHandler



; ----------------------------------------------
;  SWI ハンドラ
; ----------------------------------------------
				IMPORT	hospac_arm_imask
_HOS_SwiHandler
			; ---- SWI番号読み出し
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; カーネルコールは #10 とする
				bne 	NoKarnelCall
				
			; ---- a1 が 真なら割り込み許可
				cmp 	a1, #0
				moveq	r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				ldrne	r13, =hospac_arm_imask
				ldrne	r13, [r13]
				msr 	spsr_cf, r13
				subs	pc, lr, #0

NoKarnelCall
			; ---- 将来ここに例外処理機構 
				subs	pc, lr, #0


; ----------------------------------------------
;  SWI ハンドラ
; ----------------------------------------------
_HOS_PrefetchHandler
				b		_HOS_PrefetchHandler



; ----------------------------------------------
;  Abort ハンドラ
; ----------------------------------------------
_HOS_AbortHandler
				b		_HOS_AbortHandler



; ----------------------------------------------
;  グローバル変数
; ----------------------------------------------
				AREA	inthdr_bss, NOINIT

				EXPORT	_HOS_int_cnt
				EXPORT	_HOS_int_sp	
_HOS_int_cnt	%		4		; 割り込みネスト回数
_HOS_int_sp		%		4		; 割り込み時スタック退避


				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
