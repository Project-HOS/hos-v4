/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*   プロセッサ抽象化コンポーネント (IA32用)  コンテキスト関連処理                  */
/*                                                                           */
/*                                  Copyright (C) 1998-2002 by Project HOS   */
/*                                  http://sourceforge.jp/projects/hos/      */
/* ------------------------------------------------------------------------  */
#include "hosdenv.h"
#include "kernel.h"

#define STACK_POINTER_SIZE  4  /* スタックポインタサイズ  */
#define start_stack_addr(top,size) /*  スタック開始アドレス  */\
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
 *  あえて関数呼び出しをひとつ挟むことで, スクラッチレジスタの
 *  待避を呼出し元(本関数)に委譲することが出来る.
 *  言いかえれば, コンパイラ委せで必要なレジスタだけを待避させるようにする
 */
    __hos_pac_ia32_do_task_switch(&(pk_pre_ctxinf->sp),&(pk_nxt_ctxinf->sp));
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
