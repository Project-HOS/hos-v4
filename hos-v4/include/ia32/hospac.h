/* ------------------------------------------------------------------------*/
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (IA32��)                                   */
/*      �ץ��å���ݲ�����ݡ��ͥ�ȶ������                                   */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hospac_h__
#define __HOS_V4__IA32__hospac_h__
#include "pic.h"         /*  ����ߥ���ȥ����Ϣ����  */
#include "ioport.h"      /*  I/O �ݡ��ȴ�Ϣ����  */
#include "hosexp.h"      /*  �������㳰��Ϣ���  */
#include "descriptor.h"  /*  IA32�ǥ�������ץ���Ϣ���  */
#include "itron.h"


/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */
/* IA32��ͭ �����ߴ������� */
typedef UW		IMSK;		/* �����ߥޥ����ѥ����� */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;


/* ------------------------------------------ */
/*                �ޥ������                  */
/* ------------------------------------------ */
#define MAX_IRQ_NR  16  /*  ��������ߤκ����  */

/*  �����������å���  */
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


/*  ����ƥ������Ѥ߹���  */
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

#define hospac_del_ctx(pk_ctxinf)	/* �¹ԥ���ƥ����Ȥκ�� */

/*  �����ɥ������ 
 *  ���Ͼ����㸺�Τ����hlt̿���ȯ��
 */
#define hospac_idle()	__asm__ __volatile__("hlt\n\t")  

#define hospac_dis_int()  __asm__ __volatile__("cli\n\t")  /* �����߶ػ� */

#define hospac_ena_int()  __asm__ __volatile__("sti\n\t")  /* �����ߵ��� */

/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif
extern void hospac_ini_sys(void);  /* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */

/* �¹ԥ���ƥ����Ⱥ������� */
extern void hospac_cre_ctx(
        T_HOSPAC_CTXINF *pk_ctxinf,  /* ����ƥ����Ⱦ����Ǽ�����Ƭ���� */
        VP_INT          exinf,       /* ��ư������ */
        FP              task,        /* ��ư���� */
        SIZE            stksz,       /* �����å������� */
        VP              stk          /* �����å���Ƭ���� */
      );

  /* �¹ԥ���ƥ����Ȥ����� */
extern void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
			   T_HOSPAC_CTXINF *pk_nxt_ctxinf);
/* IA32��ͭ �����ߴ������� */
ER   chg_imsk(IMSK imsk);		/* �����ߥޥ������� */
ER   get_imsk(IMSK *p_imsk);		/* �����ߥޥ����λ��� */

ER   send_eoi(UB irq);		        /* �����ߴ�λ���� */


#ifdef __cplusplus
}
#endif

#endif  /*  __HOS_V4__IA32__hospac_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
