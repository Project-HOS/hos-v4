/* ------------------------------------------------------------------------ */
/*  ストリームデータ用 FIFOバッファ                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "stmfifo.h"



/* コンストラクタ */
void stmfifo_cre_fifo(
		T_STMFIFO *this,	/* FIFOバッファクラスのポインタ */
		UB        *buf,		/* 割り当てるバッファメモリのアドレス */
		INT       bufsz)	/* 割り当てるバッファメモリのサイズ */
{
	this->buf   = buf;
	this->bufsz = bufsz;
	this->head  = 0;
	this->tail  = 0;
}


/* デストラクタ */
void stmfifo_del_fifo(
		T_STMFIFO *this)	/* FIFOバッファクラスのポインタ */
{
	/* 特に処理は無し */
}



/* １キャラクタ書き込み */
ER stmfifo_snd_chr(
		T_STMFIFO *this,	/* FIFOバッファクラスのポインタ */
		UB        chr)		/* 書き込むキャラクタ */
{
	INT next_tail;
	
	/* 次の末尾位置計算 */
	if ( this->tail + 1 < this->bufsz )
	{
		next_tail = this->tail + 1;
	}
	else
	{
		next_tail = 0;		/* リングバッファ末尾なら折り返す */
	}
	
	/* バッファフルのチェック */
	if ( next_tail == this->head )
	{
		return E_TMOUT;
	}
	
	/* データの追加 */
	this->buf[this->tail] = chr;
	this->tail = next_tail;
	
	return E_OK;
}


/* １キャラクタ読み込み */
ER stmfifo_rcv_chr(
		T_STMFIFO *this,	/* FIFOバッファクラスのポインタ */
		UB        *p_chr)	/* １キャラクタを読み込むポインタ */
{
	/* バッファエンプティーのチェック */
	if ( this->head == this->tail )
	{
		return E_TMOUT;
	}
	
	/* データの読み出し */
	*p_chr = this->buf[this->head];
	
	/* 次の先頭位置の設定 */
	if ( this->head + 1 < this->bufsz )
	{
		this->head = this->head + 1;
	}
	else
	{
		this->head = 0;
	}
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
