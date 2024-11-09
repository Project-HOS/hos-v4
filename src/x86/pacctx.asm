; --------------------------------------------------------------------------- 
;  HOS-V4                                                                     
;    プロセッサ抽象化コンポーネント (LSI-C86 スモールモデル用)                
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


TEXT			CSEG

; -----------------------------------------------
;  割り込み禁止
;  void hospac_dis_int(void)
; -----------------------------------------------
hospac_dis_int_::
				cli					; 割り込み禁止
				ret


; -----------------------------------------------
;  割り込み許可
;  void hospac_ena_int(void)
; -----------------------------------------------
hospac_ena_int_::
				sti					; 割り込み許可
				ret


; -----------------------------------------------
;  実行コンテキストエントリーアドレス
; -----------------------------------------------
ctx_entry:		
				mov		ax, dx		; 実行時パラメータを第一引数に設定
				jmp		cx			; 実行アドレスに分岐


; -----------------------------------------------
;  実行コンテキストの作成
;  void hospac_cre_ctx_asm(
;		T_HOSPAC_CTXINF *pk_ctxinf,	/* 作成するコンテキスト */
;		VP     sp,					/* スタックポインタ */
;		void   (*task)(VP_INT),		/* 実行アドレス */
;		VP_INT exinf				/* 実行時パラメータ */
;		)
; -----------------------------------------------
hospac_cre_ctx_asm_::
				sub		bx, 2
				mov		[bx].w, ctx_entry
				sub		bx, 8
				mov		[bx], dx
				sub		bx, 2
				mov		[bx], cx
				
				xchg	ax, bx
				mov		[bx], ax
				ret


; -----------------------------------------------
;  実行コンテキストの切替
;  void hospac_swi_ctx(
;		T_HOSPAC_CTXINF *pk_pre_ctxinf,	/* 現在のコンテキストの保存先 */
;		T_HOSPAC_CTXINF *pk_nxt_ctxinf	/* 切り替えるコンテキスト */
;		)
; -----------------------------------------------
hospac_swi_ctx_::
				push	bp
				push	di
				push	si
				push	dx
				push	cx
				xchg	ax, bx
				mov		[bx], sp
				mov		bx, ax
				mov		sp, [bx]
				pop		cx
				pop		dx
				pop		si
				pop		di
				pop		bp
				ret


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
