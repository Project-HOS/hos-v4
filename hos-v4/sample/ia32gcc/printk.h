/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __sample_printk_h
#define __sample_printk_h

/* columns.  */
#define COLUMNS			80
/* lines.  */
#define LINES			25
/* attribute  */
#define ATTRIBUTE		7
/* VRAM Addresss  */
#define VRAM_ADDR               0xB8000
#define MC6845_INDEX_REG 	0x03D4
#define MC6845_DATA_REG  	0x03D5
#define printf low_printk
void cls (void);
void print_string(const char *);
void printk (const char *, ...);
void putchar (int c);
void locate(int ,int);
#endif  /*  __sample_printk_h  */
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
