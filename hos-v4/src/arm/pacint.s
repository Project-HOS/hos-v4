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
				IMPORT	hospac_arm_imsk
_HOS_SwiHandler
			; ---- SWI番号読み出し
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; カーネルコールは #10 とする
				bne 	swi_ret

			; ---- パラメーターを判定
				cmp		a1, #3
				and		a1, a1, #0x03
				addls	pc, pc, a1, lsl #2
				b		swi_ret
				b		swi_dis_int
				b		swi_ena_int

			; ---- IRQ/FIQからの復帰 (a1 = 2)
				ldr		r13, =_HOS_swi_ret
				ldmia	r13, {a1, r13, lr}
				msr		spsr_csxf, r13
				subs	pc, lr, #0

			; ---- 割り込み禁止(a1 = 0)
swi_dis_int
				mov		r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				msr 	spsr_cf, r13
				subs	pc, lr, #0

			; ---- 割り込み許可(a1 = 1)
swi_ena_int
				ldr		r13, =hospac_arm_imsk
				ldr		r13, [r13]
				msr 	spsr_cf, r13

swi_ret
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
				EXPORT	_HOS_swi_ret
_HOS_int_cnt	%		4		; 割り込みネスト回数
_HOS_int_sp		%		4		; 割り込み時スタック退避
_HOS_swi_ret	%		12		; a1, cpsr, lr の値渡し用


				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
