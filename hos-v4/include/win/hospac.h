/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS4_hospac_win_h__
#define __HOS4_hospac_win_h__



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
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* �����ƥ�ν���� */
void hospac_ena_int(void);			/* �����ߵ��� */
void hospac_dis_int(void);			/* �����߶ػ� */
void hospac_cre_cnt(T_HOSPAC_CTXINF *pk_ctxinf,
					VP_INT exinf, FP task,
					SIZE stksz, VP stk);					/* �¹ԥ���ƥ����Ȥκ��� */
void hospac_del_cnt(T_HOSPAC_CTXINF *pk_ctxinf);			/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_cnt(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* �㳰�����¹����� */
void hospac_idle(void);				/* �����ɥ���ν��� */

#ifdef __cplusplus
}
#endif


#endif	/* __HOS4_hospac_win_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
