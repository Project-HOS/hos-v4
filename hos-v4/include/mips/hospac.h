/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ����å���ݲ�����ݡ��ͥ�� (MIPS��)                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__MIPS__hospac_h__
#define __HOS_V4__MIPS__hospac_h__

/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* ����ƥ����Ⱦ�����¸�֥��å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

#define hospac_ini_sys()							/* �ץ����å���ݲ�����ݡ��ͥ�Ȥν���� */
void hospac_dis_int(void);							/* �����߶ػ� */
void hospac_ena_int(void);							/* �����ߵ��� */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* �¹ԥ���ƥ����Ȥκ���(������֥���) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf)
													/* ������֥�¦���Թ礬�����褦�˰����������ؤ� */
#define hospac_del_ctx(pk_ctxinf)					/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
#define hospac_idle()   /* �����ɥ������ */

#ifdef __cplusplus
}
#endif

#endif	/* __HOS_V4__MIPS__hospac_h__ */

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2007 by Project HOS                                  */
/* ------------------------------------------------------------------------ */