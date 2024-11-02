/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (IA32用)                               */
/*    コンテキストスイッチ処理定義                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__switch_h__
#define __HOS_V4__IA32__switch_h__
/*  タスクスイッチング  */
#define __hos_pac_ia32_do_task_switch(current_p, next_p) \
	__asm__ __volatile__(                            \
        "pushfl     \n\t"                                \
        "pushl %%ebx\n\t"                                \
        "pushl %%esi\n\t"                                \
        "pushl %%edi\n\t"                                \
        "pushl %%ebp\n\t"                                \
	"pushl $1f\n\t"                                  \
	"movl %%esp, (%0)\n\t" /* update stack val */    \
	"movl (%1), %%esp\n\t" /* get next  */           \
	"ret\n\t"                                        \
        "1:\tpopl %%ebp\n\t"                             \
        "popl %%edi\n\t"                                 \
        "popl %%esi\n\t"                                 \
        "popl %%ebx\n\t"                                 \
        "popfl\n\t"                                      \
	: /* no output */                                \
	: "r" (current_p), "r" (next_p):"memory" )


/*  コンテキスト積み込み  */
#define __hos_pac_ia32_prep_ini_stack(spp, start_func,finalizer,arg)  \
	  do{                                                         \
          __asm__ __volatile__("subl $0xc,(%0)\n\t"                   \
                               "movl (%0),%%ecx\n\t"                     \
                               "movl %1,(%%ecx)\n\t"   /* func  */       \
                               "movl %2,4(%%ecx)\n\t"   /* ext_tsk  */   \
                               "movl %3,8(%%ecx)\n\t"   /* arg */        \
                               :/* No input */                           \
			       :"r"(spp),                                \
			        "r"(start_func),"r"(finalizer),"r"(arg)  \
                               :"ecx");                                  \
          }while(0)

#define hospac_del_ctx(pk_ctxinf)	/* 実行コンテキストの削除 */

#endif  /*   __HOS_V4__IA32__switch_h__  */
