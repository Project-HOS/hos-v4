/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   H8/3048用 SCI制御ライブラリ                                            */
/*                                                                          */
/* 1. 著作者は本ソースファイルの利用によって発生する如何なる損害にもその    */
/*    責任を負いません。                                                    */
/* 2. 再配布において著作権情報及び免責事項の情報改竄を固く禁じます。        */
/* 3. 上記を守る限り、改版したものの再配布を含め、商用／非商用を問わず      */
/*    あらゆる用途に自由に利用できます。                                    */
/* 4. 改版物の再配布時は、改版者の著作情報と連絡先を必ず追記してください。  */
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
