/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   ARM用 Cライブラリ用関数                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include <stdio.h>
#include <rt_misc.h>


/* セミホスティング用SWI番号定義 */
#define SemiSWI		0x123456


/* １文字出力（セミホスティング） */
__swi(SemiSWI) void _WriteC(unsigned op, char *c);
#define WriteC(c) _WriteC (0x3,c)

/* exit（セミホスティング） */
__swi(SemiSWI) void _Exit(unsigned op, unsigned except);
#define Exit() _Exit (0x18,0x20026)



/* １文字出力 */
int fputc(int ch, FILE *f)
{
    char tmp = ch;

    WriteC(&tmp);

    return ch;
}


/* ファイルエラー取得 */
int ferror(FILE *f)
{
    return EOF;
}


/* プロセス終了 */
void _sys_exit(int return_code)
{
    Exit();
}


/* ターミナル出力 */
void _ttywrch(int ch)
{
}



static unsigned int heap_area[4096];	/* malloc 用ヒープエリア */

/* ヒープ管理用アドレス設定 */
__value_in_regs struct __initial_stackheap __user_initial_stackheap(
        unsigned R0, unsigned SP, unsigned R2, unsigned SL)
{
    struct __initial_stackheap config;
    
    config.heap_base  = (unsigned long)heap_area;
    config.heap_limit = (unsigned long)&heap_area[4096];
    config.stack_base = SP;

    return config;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
