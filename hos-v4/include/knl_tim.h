/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ���ִ���                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tim_h__
#define __HOS_V4__knl_tim_h__



#include "knl_hos.h"



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �����ޥ��֥������ȹ�¤�� */
typedef struct t_kernel_tim
{
	struct t_kernel_tim *next;
	struct t_kernel_tim *prev;
	FP                  timhdr;
} T_KERNEL_TIM;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ƥ������� */
extern const UW kernel_tic_deno;				/* ����ե�����졼������ TIC_DENO ������ */
extern const UW kernel_tic_div;					/* ����ե�����졼������ TIC_NUME / TIC_DENO ������ */
extern const UW kernel_tic_mod;					/* ����ե�����졼������ TIC_NUME % TIC_DENO ������ */
extern UW       kernel_tic_cnt;					/* ������ƥ��å��ѥ����� */
extern SYSTIM   kernel_systim;					/* �����ƥ���� */


/* �����ޥꥹ�ȴ��� */
extern T_KERNEL_TIM *kernel_tml_head;	/* �����ޥꥹ����Ƭ���� */
extern T_KERNEL_TIM *kernel_tml_ptr;	/* �����ޥꥹ�ȥݥ��� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �����ƥ������� */
void    kernel_ini_tim(void);						/* ���ִ�����ǽ�ν���� */
ER      set_tim(const SYSTIM *p_systim);			/* �����ƥ��������� */
ER      get_tim(SYSTIM *p_systim);					/* �����ƥ����μ��� */
ER      isig_tim(void);								/* ������ƥ��å��ζ��� */

/* �����ޥꥹ����� */
void    kernel_add_tml(T_KERNEL_TIM *timobj);		/* �����ޥ��֥������ȤΥꥹ�Ȥؤ��ɲ� */
void    kernel_rmv_tml(T_KERNEL_TIM *timobj);		/* �����ޥ��֥������ȤΥꥹ�Ȥ���κ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tim_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
