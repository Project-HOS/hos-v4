#ifndef __H8TINY_SCI_H_
#define __H8TINY_SCI_H_


/* SCI通信速度定義 (16MHzのとき) */
#define SCI_2400   207
#define SCI_4800   103
#define SCI_9600    51
#define SCI_19200   25
#define SCI_31250   15
#define SCI_38400   12
#define SCI_57600    8		/* 誤差 -3.5% ぎりぎりいけるかも (^^;; */

/* SCI3 */
void SCI3_Initialize(unsigned char rate);	/* SCI3初期化 */
void SCI3_PutChar(char c);			/* １文字出力 */

/* assign SCI3 for SCI*/
#define Sci_Initialize SCI3_Initialize
#define Sci_PutChar SCI3_PutChar

#endif /* __H8TINY_SCI_H__ */
