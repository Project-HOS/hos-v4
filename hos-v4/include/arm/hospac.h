/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (ARM ��)                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__ARM__hospac_h__
#define __HOS_V4__ARM__hospac_h__



#include "itron.h"



/* ------------------------------------------ */
/*                   �����                   */
/* ------------------------------------------ */

/* ����ƥ����Ⱦ�����¸�֥�å� */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

#define hospac_ini_sys()	hos_arm_ini_int()		/* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */
void hospac_dis_int(void);							/* �����߶ػ� */
void hospac_ena_int(void);							/* �����ߵ��� */
void hospac_cre_cnt_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* �¹ԥ���ƥ����Ȥκ���(������֥���) */
#define hospac_cre_cnt(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_cnt_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf);
													/* ������֥�¦���Թ礬�����褦�˰����������ؤ� */
#define hospac_del_cnt(pk_ctxinf)					/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_swi_cnt(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* �㳰�����¹����� */

#define hospac_idle()				/* �����ɥ������ */

void  hos_arm_ini_int(void);		/* �����߽����ν�����ʥ桼���������ؿ��� */ 
INTNO hos_arm_sta_irq(void);		/* IRQ�����߽������ϡʥ桼���������ؿ��� */
void  hos_arm_end_irq(void);		/* IRQ�����߽�����λ�ʥ桼���������ؿ��� */
INTNO hos_arm_sta_fiq(void);		/* FIQ�����߽������ϡʥ桼���������ؿ��� */
void  hos_arm_end_fiq(void);		/* FIQ�����߽�����λ�ʥ桼���������ؿ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__ARM__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
