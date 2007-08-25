/* ------------------------------------------------------------------------*/
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (IA32��)                                   */
/*      �ץ��å���ݲ�����ݡ��ͥ�ȶ������                                   */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hospac_h__
#define __HOS_V4__IA32__hospac_h__
#include "pic.h"                 /*  ����ߥ���ȥ����Ϣ����  */
#if defined(__GNUC__ ) 
#include "ia32gcc/linkage.h"     /*  gcc ��ͭ��󥱡������  */
#include "ia32gcc/ioport.h"      /*  I/O �ݡ��ȴ�Ϣ����  */
#include "ia32gcc/hosexp.h"      /*  �������㳰��Ϣ���  */
#include "ia32gcc/descriptor.h"  /*  IA32�ǥ�������ץ���Ϣ���  */
#include "ia32gcc/switch.h"  /*  IA32�ǥ�������ץ���Ϣ���  */
#include "ia32gcc/idle.h"    /*  IA32�����ɥ������Ϣ���  */
#else
#error "IA32 port can not support your compiler."
#endif  /*  __GNUC__  */
#include "itron.h"


/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */
/* IA32��ͭ �����ߴ������� */
typedef UH		IMSK;		/* �����ߥޥ����ѥ����� */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;


/* ------------------------------------------ */
/*                �ޥ������                  */
/* ------------------------------------------ */
#define MAX_IRQ_NR  16  /*  ��������ߤκ����  */


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

ER   _kernel_ia32__send_eoi(UW irq);	/* �����ߴ�λ���� */


#ifdef __cplusplus
}
#endif

#endif  /*  __HOS_V4__IA32__hospac_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
