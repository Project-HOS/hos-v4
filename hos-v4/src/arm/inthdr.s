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
_HOS_SwiHandler
			; ---- SWI番号読み出し
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; カーネルコールは #10 とする
				bne 	NoKarnelCall
				
			; ---- a1 が 真なら割り込み許可
				cmp 	a1, #0
				moveq	r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				movne	r13, #Mode_USR
				msr 	spsr_cf, r13
				subs	pc, lr, #0

NoKarnelCall
				; カーネル以外でswiを利用するならここに書く
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



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
