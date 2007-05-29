; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                     
;    プロセッサ抽象化コンポーネント (ARM用)                                   
;    例外ハンドラ                                                             
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


				INCLUDE	pacarm.inc



				AREA	inthdr_code, CODE, READONLY
				CODE32

				EXPORT	_HOS_CpuExceptionHandler

; ----------------------------------------------
;  CPU例外ハンドラ
; ----------------------------------------------
				IMPORT	kernel_sta_exc				; CPU例外ハンドラ開始処理
				IMPORT	kernel_end_exc				; CPU例外ハンドラ終了処理
				IMPORT	kernel_exe_exc				; CPU例外ハンドラの実行
				IMPORT	kernel_int_sp				; 割り込み用スタックアドレス
				IMPORT	_HOS_int_cnt				; 割り込みネスト回数
				IMPORT	_HOS_int_sp					; 割り込み時スタック退避
				
_HOS_CpuExceptionHandler
			; ---- Systemモードに移行してレジスタ退避
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; 汎用レジスタ退避

			; ---- 元のモードに戻ってspsr保存
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_UND
				msr		cpsr_c, r1
				mrs		r1, spsr					; spsr 取り出し
				mov		r2, lr						; 割り込み復帰先保存
				
			; ---- USRモードに移行
				mov		r3, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r3
				
			; ---- レジスタ退避
				stmfd	sp!, {r0-r2}				; a1, spsr_irq, lr_irq 保存
				
			; ---- 多重割り込みチェック
				ldr		r0, =_HOS_int_cnt
				ldr		r1, [r0]					; 割り込みネストカウンタ取得
				cmp		r1, #0
				add		r1, r1, #1					; 割り込みネストカウンタインクリメント
				str		r1, [r0]
				bne		MultipleInt					; 割り込み中なら分岐
				
			; ---- スタックの入れ替え
				ldr		r0, =_HOS_int_sp
				str		sp, [r0]					; スタックポインタを退避
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; 割り込み用スタックを設定

			; ---- CPU例外ハンドラ処理の開始
				bl		kernel_sta_exc				; CPU例外ハンドラ開始処理
				bl		kernel_exe_exc				; 割り込み処理実行
			
			; ---- スタックの復帰
				ldr		r0, =_HOS_int_sp
				ldr		sp, [r0]					; スタックポインタを復帰
			
			; ---- 割り込みネストカウントデクリメント
				ldr		r0, =_HOS_int_cnt
				mov		r1, #0
				str		r1, [r0]					; 割り込みネストカウンタクリア
			
			; ---- 遅延ディスパッチ実行
				bl		kernel_end_exc				; 遅延ディスパッチ実行
			
			; ---- CPU例外ハンドラからの復帰
ReturnExc		
				IMPORT	_HOS_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =_HOS_swi_ret
				stmia	r3, {r0-r2}					; 割り込み復帰データ設定
				ldmfd	sp!, {r1-r3, ip, lr}		; レジスタ復帰
				mov		a1, #2
				swi		0x10


			;---- 割り込み中の処理
MultipleInt
			; ---- 割り込み処理
				bl		kernel_sta_exc				; CPU例外ハンドラ開始処理

			; ---- 割り込みネストカウントデクリメント
				ldr		r0, =_HOS_int_sp
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnExc



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
