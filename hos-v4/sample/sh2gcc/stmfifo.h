/* ------------------------------------------------------------------------ */
/*  ストリームデータ用 FIFOバッファ                                         */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __stmfifo_h__
#define __stmfifo_h__


/* FIFOバッファ */
typedef struct t_stmfifo
{
	UB  *buf;		/* バッファ用メモリの先頭アドレス */
	INT bufsz;		/* バッファ用メモリのサイズ */
	INT head;		/* データ先頭位置 */
	INT tail;		/* データ末尾位置 */
} T_STMFIFO;


#ifdef __cplusplus
extern "C" {
#endif

void stmfifo_cre_fifo(T_STMFIFO *this, UB *buf, INT bufsz);		/* コンストラクタ */
void stmfifo_del_fifo(T_STMFIFO *this);							/* デストラクタ */

ER   stmfifo_snd_chr(T_STMFIFO *this, UB chr);					/* １キャラクタ書き込み */
ER   stmfifo_rcv_chr(T_STMFIFO *this, UB *p_chr);				/* １キャラクタ読み込み */

#ifdef __cplusplus
}
#endif


#endif	/* __stmfifo_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */
/* ------------------------------------------------------------------------ */
