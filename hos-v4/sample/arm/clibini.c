/* ------------------------------------------------------------------------ */
/*  HOS-V4 ����ץ�                                                         */
/*   ARM�� C�饤�֥���Ѵؿ�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include <stdio.h>
#include <rt_misc.h>


/* ���ߥۥ��ƥ�����SWI�ֹ���� */
#define SemiSWI		0x123456


/* ��ʸ�����ϡʥ��ߥۥ��ƥ��󥰡� */
__swi(SemiSWI) void _WriteC(unsigned op, char *c);
#define WriteC(c) _WriteC (0x3,c)

/* exit�ʥ��ߥۥ��ƥ��󥰡� */
__swi(SemiSWI) void _Exit(unsigned op, unsigned except);
#define Exit() _Exit (0x18,0x20026)



/* ��ʸ������ */
int fputc(int ch, FILE *f)
{
    char tmp = ch;

    WriteC(&tmp);

    return ch;
}


/* �ե����륨�顼���� */
int ferror(FILE *f)
{
    return EOF;
}


/* �ץ�����λ */
void _sys_exit(int return_code)
{
    Exit();
}


/* �����ߥʥ���� */
void _ttywrch(int ch)
{
}



static unsigned int heap_area[4096];	/* malloc �ѥҡ��ץ��ꥢ */

/* �ҡ��״����ѥ��ɥ쥹���� */
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
