; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  日立 H8 用 サンプルプログラム                   
;    スタートアップルーチン                                                   
;                                                                             
;  1. 著作者は本ソースファイルの利用によって発生する如何なる損害にもその      
;     責任を負いません。                                                      
;  2. 再配布において著作権情報及び免責事項の情報改竄を固く禁じます。          
;  3. 上記を守る限り、改版したものの再配布を含め、商用／非商用を問わず        
;     あらゆる用途に自由に利用できます。                                      
;  4. 改版物の再配布時は、改版者の著作情報と連絡先を必ず追記してください。    
;                                                                             
;                                   Copyright (C) 1998-2002 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 



		.h8300h

; -------------------------------------
;  スタートアップルーチン
; -------------------------------------
		.text
		.align 2
		.global _startup
_startup:
		; ----- スタック初期化
		mov.l	#_stack,er7

		; ----- .data セクションコピー （DATAが64kbyte以下と仮定）
		mov.l	#___dtors_end,er5
		mov.l	#___data,er6
		mov.w	#data_size,r4
copy_dsec:	eepmov.w
		mov.w	r4,r4
		bne	copy_dsec

		; ----- .bss セクションクリア（BSSが64kbyte以下と仮定）
		mov.l	#_bss_start,er5
		mov.l	#_bss_start+1,er6
		mov.w	#bss_size,r4
		mov.b	#0,r0l
		mov.b	r0l,@er5
clr_bsec:	eepmov.w
		mov.w	r4,r4
		bne	clr_bsec

		; ----- 初期化ルーチン呼び出し
		jsr	@_main
idle_loop:
		bra	idle_loop

		.end



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
