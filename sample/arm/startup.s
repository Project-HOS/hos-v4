; --------------------------------------------------------------------------- 
;  HOS-V4 サンプルプログラム                                                  
;    スタートアップルーチン (ARM 用)                                          
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 



; スタックアドレス定義
Stack			EQU		0x00400000


; 定数定義
Mode_USR		EQU 	0x10
Mode_SVC		EQU 	0x13

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40
T_Bit			EQU 	0x20

SVC_Stack		EQU 	Stack		; SVCモードのスタック
USR_Stack		EQU 	Stack-32	; USERモードのスタック


				IMPORT	|Image$$RO$$Limit|
				IMPORT	|Image$$RW$$Base|
				IMPORT	|Image$$ZI$$Base|
				IMPORT	|Image$$ZI$$Limit|
				IMPORT  _HOS_UndefinedHandler
				IMPORT  _HOS_SwiHandler
				IMPORT	_HOS_PrefetchHandler
				IMPORT	_HOS_AbortHandler
				IMPORT	_HOS_IrqHandler
				IMPORT  _HOS_FiqHandler


				AREA	Init, CODE, READONLY

; スタートアップ
				ENTRY

		IF :DEF: ROM_AT_ADDRESS_ZERO
; --- ROM化する場合のベクター定義
				b	 	Reset_Handler
				b	 	_HOS_UndefinedHandler
				b	 	_HOS_SwiHandler
				b	 	_HOS_PrefetchHandler
				b	 	_HOS_AbortHandler
				nop
				b	 	_HOS_IrqHandler
				b	 	_HOS_FiqHandler
		ELSE
; --- ICE 等を使う場合は起動後にベクタをコピー
				mov 	r8, #0
				adr 	r9, Vector_Init_Block
				ldmia	r9!, {r0-r7}
				stmia	r8!, {r0-r7}
				ldmia	r9!, {r0-r7}
				stmia	r8!, {r0-r7}

Vector_Init_Block
				ldr 	pc, Reset_Addr
				ldr 	pc, Undefined_Addr
				ldr 	pc, SWI_Addr
				ldr 	pc, Prefetch_Addr
				ldr 	pc, Abort_Addr
				nop
				ldr 	pc, IRQ_Addr
				ldr 	pc, FIQ_Addr
		ENDIF

Reset_Addr		DCD 	Reset_Handler
Undefined_Addr	DCD 	_HOS_UndefinedHandler
SWI_Addr		DCD 	_HOS_SwiHandler
Prefetch_Addr	DCD 	_HOS_PrefetchHandler
Abort_Addr		DCD 	_HOS_AbortHandler
IRQ_Addr		DCD 	_HOS_IrqHandler
FIQ_Addr		DCD 	_HOS_FiqHandler



; -----------------------------------------------
;  リセットハンドラ
; -----------------------------------------------
Reset_Handler
		; --- SVCモードの初期化
				mov 	r0, #Mode_SVC:OR:I_Bit:OR:F_Bit
				msr 	cpsr_cf, r0
				ldr 	r13, =SVC_Stack			; SVCモードのスタックを設定

		; --- C言語用データ設定
				ldr 	r0, =|Image$$RO$$Limit|
				ldr 	r1, =|Image$$RW$$Base|
				ldr 	r3, =|Image$$ZI$$Base|
				
		; --- RW 領域のコピー
				cmp 	r0, r1
				beq 	rw_copy_end
rw_copy_loop	
				cmp 	r1, r3
				ldrcc	r2, [r0], #4
				strcc	r2, [r1], #4
				bcc 	rw_copy_loop
rw_copy_end 	
		
		; --- ZI 領域の初期化
				ldr 	r1, =|Image$$ZI$$Limit|
				mov 	r2, #0
zi_ini_loop
				cmp 	r3, r1
				strcc	r2, [r3], #4
				bcc 	zi_ini_loop

		; --- USRモードに移行
				mov 	r0, #Mode_USR:OR:I_Bit:OR:F_Bit
				msr 	cpsr_cf, r0
				ldr 	sp, =USR_Stack

		; --- C言語コードにジャンプ
				IMPORT	__rt_entry
				b		__rt_entry				; Cライブラリの初期化アドレス


				END



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
