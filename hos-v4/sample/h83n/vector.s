; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  サンプルプログラム                              
;    割り込みベクターテーブル                                                 
;                                                                             
;                                   Copyright (C) 1998-2003 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 

		.h8300h

; -----------------------------------------------
;          割り込みベクタテーブル
; -----------------------------------------------
		.section	.vectors

		.word	_startup
		.word	0xffff			;_hos_vector001; 
		.word	0xffff			;_hos_vector002; 
		.word	0xffff			;_hos_vector003; 
		.word	0xffff			;_hos_vector004; 
		.word	0xffff			;_hos_vector005; 
		.word	0xffff			;_hos_vector006; 
		.word	_hos_vector007
		.word	_hos_vector008
		.word	_hos_vector009
		.word	_hos_vector010
		.word	_hos_vector011
		.word	_hos_vector012
		.word	_hos_vector013
		.word	_hos_vector014
		.word	_hos_vector015
		.word	_hos_vector016
		.word	_hos_vector017
		.word	_hos_vector018
		.word	_hos_vector019
		.word	0xffff			;_hos_vector020; 
		.word	_hos_vector021
		.word	_hos_vector022
		.word	_hos_vector023
		.word	_hos_vector024
		.word	_hos_vector025

		.end



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2003 by Project HOS                                     
; --------------------------------------------------------------------------- 
