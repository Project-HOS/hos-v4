; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    例外ハンドラ                                                            
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------


; 定数定義
Mode_USR		EQU 	0x10
Mode_IRQ		EQU 	0x12
Mode_SYS		EQU 	0x1f

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40



				AREA	inthdr_code, CODE, READONLY

				EXPORT	_HOS_IrqHandler

; ----------------------------------------------
;  IRQ ハンドラ
; ----------------------------------------------
				IMPORT	hos_arm_sta_irq
				IMPORT	hos_arm_end_irq
				IMPORT	mknl_exe_int
				IMPORT	mknl_end_int
_HOS_IrqHandler
				sub		lr, lr, #4				; リターンアドレス算出
			
			; ---- Systemモードに移行してレジスタ退避
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_c, r13
				stmfd	sp!, {r0-r3, ip, lr, pc}	; 汎用レジスタ退避
				mov		r0, sp

			; ---- IRQモードに戻るってとspsr保存				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_IRQ
				msr		cpsr_c, r1
				str		lr, [r0, #24]			; 割り込み復帰先保存
				mrs		r0, spsr				; spsr 取り出し
				
			; ---- USRモードに移行
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r1
				stmfd	sp!, {r0}				; 割り込み元フラグ保存
				
			; ---- 割り込み処理
				bl      hos_arm_sta_irq			; IRQ開始処理(割込み番号取得)
				bl		mknl_exe_int			; 割り込み処理実行
				bl		hos_arm_end_irq			; IRQ終了処理
				bl		mknl_end_int			; 割り込みの終了処理
				
			; ---- 割り込み許可
				mov	a1, #1		; 割り込み許可を指定
				swi	0x10		; スーパバイーザーコール
				
				ldmfd	sp!, {r0}
				msr		cpsr_sxf, r0
				ldmfd	sp!, {r0-r3, ip, lr, pc}	; レジスタ復帰＆リターン

				

				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
