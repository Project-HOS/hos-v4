/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (ARM ��)                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__ARM__hospac_h__
#define __HOS_V4__ARM__hospac_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ARM��ͭ �����ߴ������� */
#define ARM_IMSK_USR_MODE		0x00000010		/* �桼�����⡼�� */
#define ARM_IMSK_FIQ			0x00000040		/* FIQ�ޥ����ӥå� */
#define ARM_IMSK_IRQ			0x00000080		/* IRQ�ޥ����ӥå� */



/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �����å��ݥ�����¸�ΰ� */
} T_HOSPAC_CTXINF;


/* ARM��ͭ �����ߴ������� */
typedef UW		IMASK;			/* �����ߥޥ��� */



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

extern UW hospac_arm_imsk;		/* �����ߥޥ��� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#define hospac_ini_sys()	hos_arm_ini_int()		/* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */
void hospac_dis_int(void);							/* �����߶ػ� */
void hospac_ena_int(void);							/* �����ߵ��� */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* �¹ԥ���ƥ����Ȥκ���(������֥���) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf);
													/* ������֥�¦���Թ礬�����褦�˰����������ؤ� */
#define hospac_del_ctx(pk_ctxinf)					/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */

#define hospac_idle()				/* �����ɥ������ */

void  hos_arm_ini_int(void);		/* �����߽����ν�����ʥ桼���������ؿ��� */ 
INTNO hos_arm_sta_irq(void);		/* IRQ�����߽������ϡʥ桼���������ؿ��� */
void  hos_arm_end_irq(void);		/* IRQ�����߽�����λ�ʥ桼���������ؿ��� */
INTNO hos_arm_sta_fiq(void);		/* FIQ�����߽������ϡʥ桼���������ؿ��� */
void  hos_arm_end_fiq(void);		/* FIQ�����߽�����λ�ʥ桼���������ؿ��� */


/* ARM��ͭ �����ߴ������� */
ER    chg_imsk(IMASK imsk);			/* �����ߥޥ������� */
ER    get_imsk(IMASK *p_imsk);		/* �����ߥޥ����λ��� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__ARM__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
