/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (��Ω H8/300H ��)                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__H83__hospac_h__
#define __HOS_V4__H83__hospac_h__



#include "itron.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �����ߥޥ������ */
#define H83_IMSK_I_BIT		0x80	/* �����ߥޥ����ӥå� */
#define H83_IMSK_UI_BIT		0x40	/* �桼�����ӥåȡ������ߥޥ����ӥå� */

#define H83_IMSK_LEVEL0		0x00								/* �ץ饤����ƥ�����٥�0/1����� */
#define H83_IMSK_LEVEL1		(H83_IMSK_I_BIT)					/* �ץ饤����ƥ�����٥�1�Τߵ��� */
#define H83_IMSK_LEVEL2		(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)	/* ���٤ƶػ� */



/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

typedef UB	IMSK;		/* �����ߥޥ��� */


/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

extern UB kernel_h83_imsk;		/* �����ߥޥ����� */
extern UB kernel_h83_ibmsk;		/* �����ߥ١����ޥ����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* �����ƥ�ν���� */

void hospac_dis_int(void);			/* �����߶ػ� */
void hospac_ena_int(void);			/* �����ߵ��� */

void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);			/* �¹ԥ���ƥ����Ȥκ���(������֥���) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf)
															/* ������֥�¦���Թ礬�����褦�˰����������ؤ� */
#define hospac_del_ctx(pk_ctxinf)	do {} while (0)			/* �¹ԥ���ƥ����Ȥκ��(����) */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
#define hospac_idle()	do {} while (0)						/* �����ɥ����ư��(���⤷�ʤ�) */


ER chg_imsk(IMSK imsk);				/* �����ߥޥ����Υ١����ͤ��ѹ� */
ER get_imsk(IMSK *p_imsk);			/* �����ߥޥ����Υ١����ͤλ��� */

ER fchg_imsk(IMSK imsk);			/* ���ߤγ���ߥޥ����ͤζ����ѹ� */
ER fget_imsk(IMSK *p_imsk);			/* ���ߤγ���ߥޥ����ͤζ������� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__H83__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
