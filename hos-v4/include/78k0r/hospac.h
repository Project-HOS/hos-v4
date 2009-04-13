/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (78K0R��)                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2009 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__78K0R__hospac_h__
#define __HOS_V4__78K0R__hospac_h__

/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;

/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#define	hospac_ini_sys()								/* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */
#define	hospac_idle()									/* �����ɥ������ */
#if 1
#define	hospac_dis_int()	__asm("DI")					/* �����߶ػ� */
#define	hospac_ena_int()	__asm("EI")					/* �����ߵ��� */
#else
extern	void	hospac_dis_int( void );					/* �����߶ػ� */
extern	void	hospac_ena_int( void );					/* �����ߵ��� */
#endif

void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf, VP_INT exinf, FP task, unsigned short stk);
														/* �¹ԥ���ƥ����Ȥκ���(������֥���) */

#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
		hospac_cre_ctx_asm(pk_ctxinf, exinf, task, (SIZE)stk+stksz)
														/* �¹ԥ���ƥ����Ȥκ��� */

#define hospac_del_ctx(pk_ctxinf)						/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */

#endif	/* __HOS_V4__78K0R__hospac_h__ */

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2009 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
