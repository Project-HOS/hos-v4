/* ------------------------------------------------------------------------ */
/*  H8/3048用 SCI制御ライブラリ                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __PROJECT_HOS__h8_sci_h__
#define __PROJECT_HOS__h8_sci_h__



/* SCI通信速度定義 (16MHzのとき) */
#define SCI_2400   207
#define SCI_4800   103
#define SCI_9600    51
#define SCI_19200   25
#define SCI_31250   15
#define SCI_38400   12
#define SCI_57600    8		/* 誤差 -3.5% ぎりぎりいけるかも (^^;; */



/* SCI */
void SCI_Init(unsigned char rate);	/* SCI初期化 */
void SCI_ERR_Intr(void);			/* エラー受信 割り込みハンドラ */
void SCI_RX_Intr(void);				/* データ受信 割り込みハンドラ */
void SCI_TX_Intr(void);				/* 送信バッファ空き割り込み */
void SCI_Putc(char c)			;	/* １文字出力 */
int  SCI_Getc(void);				/* １文字入力 */
void SCI_Puts(const char* str);		/* 文字列出力 */
void SCI_Gets(char* buf);			/* 文字列入力 */



#endif	/* __PROJECT_HOS__h8_sci_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
