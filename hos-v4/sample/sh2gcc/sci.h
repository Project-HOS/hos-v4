/* ------------------------------------------------------------------------ */
/*  SH7045 SCI制御                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __sci_h__
#define __sci_h__


#define ID_SCI0			1
#define ID_SCI1			2

#define SCI_SND_BUFSZ	128
#define SCI_RCV_BUFSZ	128


#ifdef __cplusplus
extern "C" {
#endif

void    sci_init(VP_INT exinf);			/* 初期化 */
ER      sci_open(ID id, UB brr);		/* オープン */
ER      sci_close(ID id);				/* クローズ */
ER      sci_putc(ID id, UB chr);		/* １文字出力 */
ER_UINT sci_puts(ID id, const UB *str);	/* 文字列出力 */
ER_UINT sci_getc(ID id);				/* １文字入力 */
ER_UINT sci_gets(ID id, UB *str);		/* 文字列入力 */

void    sci_snd_hdr(VP_INT exinf);		/* 送信割り込みハンドラ */
void    sci_rcv_hdr(VP_INT exinf);		/* 受信割り込みハンドラ */

#ifdef __cplusplus
}
#endif


#endif


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
