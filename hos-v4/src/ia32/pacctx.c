/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                   */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (IA32��)  ����ƥ����ȴ�Ϣ����                  */
/*                                                                           */
/*                                  Copyright (C) 1998-2002 by Project HOS   */
/*                                  http://sourceforge.jp/projects/hos/      */
/* ------------------------------------------------------------------------  */
#include "hosdenv.h"
#include "kernel.h"

#define STACK_POINTER_SIZE  4  /* �����å��ݥ��󥿥�����  */
#define start_stack_addr(top,size) /*  �����å����ϥ��ɥ쥹  */\
           ((top)+((size) & (~STACK_POINTER_SIZE)))

void 
hospac_cre_ctx(T_HOSPAC_CTXINF *pk_ctxinf, 
	       VP_INT exinf, 
	       FP task, 
	       SIZE stksz, 
	       VP  stk)
{

  pk_ctxinf->sp=(VP)start_stack_addr((UW)stk,(UW)stksz);
  __hos_pac_ia32_prep_ini_stack(&(pk_ctxinf->sp),task, ext_tsk,exinf);
}

void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
		    T_HOSPAC_CTXINF *pk_nxt_ctxinf)
{
/*
 *  �����ƴؿ��ƤӽФ���ҤȤĶ��ळ�Ȥ�, ������å��쥸������
 *  �����ƽФ���(�ܴؿ�)�˰Ѿ����뤳�Ȥ������.
 *  �����������, ����ѥ���Ѥ���ɬ�פʥ쥸�������������򤵤���褦�ˤ���
 */
    __hos_pac_ia32_do_task_switch(&(pk_pre_ctxinf->sp),&(pk_nxt_ctxinf->sp));
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
