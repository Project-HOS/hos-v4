/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (��Ω SH ��)                           */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__SH__hospac_h__
#define __HOS_V4__SH__hospac_h__



/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* SH��ͭ �����ߴ������� */
typedef UW		IMSK;			/* �����ߥޥ��� */


/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;



#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#define hospac_ini_sys()							/* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */
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
#define hospac_idle()				/* �����ɥ������ */


/* SH��ͭ �����ߴ������� */
ER   chg_imsk(IMSK imsk);			/* �����ߥޥ������� */
ER   get_imsk(IMSK *p_imsk);		/* �����ߥޥ����λ��� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__SH__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
