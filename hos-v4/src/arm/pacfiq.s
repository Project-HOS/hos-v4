; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    例外ハンドラ                                                            
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------


; 定数定義
Mode_USR		EQU 	0x10
Mode_FIQ		EQU 	0x11
Mode_SYS		EQU 	0x1f

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40



				AREA	inthdr_code, CODE, READONLY

				EXPORT  _HOS_FiqHandler

; ----------------------------------------------
;  FIQ ハンドラ
; ----------------------------------------------
				IMPORT	hos_arm_sta_fiq				; FIQの初期化処理
				IMPORT	hos_arm_end_fiq				; FIQの終了処理
				IMPORT	kernel_sta_int				; 割り込み終了開始
				IMPORT	kernel_end_int				; 割り込み終了処理
				IMPORT	kernel_exe_int				; 割り込み処理の実行
				IMPORT	kernel_int_sp				; 割り込み用スタックアドレス
				IMPORT	_HOS_int_cnt				; 割り込みネスト回数
				IMPORT	_HOS_int_sp					; 割り込み時スタック退避
				
_HOS_FiqHandler
				sub		lr, lr, #4					; リターンアドレス算出
			
			; ---- Systemモードに移行してレジスタ退避
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_c, r13
				stmfd	sp!, {r0-r3, ip, lr, pc}	; 汎用レジスタ退避
				mov		r0, sp

			; ---- IRQモードに戻るってとspsr保存				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_FIQ
				msr		cpsr_c, r1
				str		lr, [r0, #24]				; 割り込み復帰先保存
				mrs		r0, spsr					; spsr 取り出し
				
			; ---- USRモードに移行
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r1
				stmfd	sp!, {r0}					; 割り込み元フラグ保存
				
			; ---- 多重割り込みチェック
				ldr		r0, =_HOS_int_cnt
				ldr		r1, [r0]					; 割り込みネストカウンタ取得
				cmp		r1, #0
				add		r1, r1, #1					; 割り込みネストカウンタインクリメント
				str		r1, [r0]
				bne		MultipleInt					; 多重割り込みなら分岐
				
			; ---- スタックの入れ替え
				ldr		r0, =_HOS_int_sp
				str		sp, [r0]					; スタックポインタを退避
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; 割り込み用スタックを設定

			; ---- 割り込み処理の開始
				bl		kernel_sta_int
				
			; ---- 割り込み処理
				bl      hos_arm_sta_fiq				; IRQ開始処理(割込み番号取得)
				bl		kernel_exe_int				; 割り込み処理実行
				bl		hos_arm_end_fiq				; IRQ終了処理
			
			; ---- スタックの復帰
				ldr		r0, =_HOS_int_sp
				ldr		sp, [r0]					; スタックポインタを復帰
			
			; ---- 割り込みネストカウントデクリメント
				ldr		r0, =_HOS_int_cnt
				mov		r1, #0
				str		r1, [r0]					; 割り込みネストカウンタクリア
			
			; ---- 遅延ディスパッチ実行
				bl		kernel_end_int				; 遅延ディスパッチ実行
			
			; ---- 割り込みからの復帰
ReturnInt			
				mov		a1, #1						; 割り込み許可を指定
				swi		0x10						; スーパバイーザーコール
				
				ldmfd	sp!, {r0}
				msr		cpsr_sxf, r0
				ldmfd	sp!, {r0-r3, ip, lr, pc}	; レジスタ復帰＆リターン


			;---- 多重割り込み処理
MultipleInt
			; ---- 割り込み処理
				bl      hos_arm_sta_fiq				; IRQ開始処理(割込み番号取得)
				bl		kernel_exe_int				; 割り込み処理実行
				bl		hos_arm_end_fiq				; IRQ終了処理

			; ---- 割り込みネストカウントデクリメント
				ldr		r0, =_HOS_int_cnt
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnInt



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
