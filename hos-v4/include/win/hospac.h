/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__win__hospac_h__
#define __HOS_V4__win__hospac_h__



/* Windows �إå��ե�������ɤߤ��� */
#define SIZE  WIN_SIZE
#include <windows.h>
#undef  SIZE

/*   Windows ɸ��� SIZE ��¤�Τ� ITRON ��ɸ�෿�ȽŤʤ�Τ� */
/* �嵭�Τ褦�˶���Ū�� WIN_SIZE ��̾�����Ѥ��Ƥ���          */
/* Windows API�� SIZE �����Ѥ���Ȥ��������                 */

#include <itron.h>



/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	HANDLE hThread;			/* ����åɥϥ�ɥ� */
	DWORD  dwThreadId;		/* ����å�ID */
	BOOL   blIntSuspend;	/* �����ߤǤΥ����ڥ�ɥե饰 */
} T_HOSPAC_CTXINF;


/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

extern HANDLE hospac_hSem;		/* �����ƥ����¾�����ѥ��ޥե� */
extern BOOL   hospac_blInt;		/* �����߽�����ե饰 */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* �����ƥ�ν���� */
void hospac_ena_int(void);			/* �����ߵ��� */
void hospac_dis_int(void);			/* �����߶ػ� */

void hospac_cre_ctx(T_HOSPAC_CTXINF *pk_ctxinf,
					VP_INT exinf, FP task,
					SIZE stksz, VP stk);					/* �¹ԥ���ƥ����Ȥκ��� */
void hospac_del_ctx(T_HOSPAC_CTXINF *pk_ctxinf);			/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* �㳰�����¹����� */
void hospac_idle(void);				/* �����ɥ���ν��� */


void hospac_win_int(INTNO intno);	/* ���������ߤΥ��ߥ�졼��(ITRON�������Ȥ�̵�ط��Υ���åɤ���Ƥ֤���) */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__win__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
