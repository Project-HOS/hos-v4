/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (��Ω H8 300h ��)                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS4_hospac_h8_300_h__
#define __HOS4_hospac_h8_300_h__



#include <itron.h>



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

void hospac_ini_sys(void);			/* �����ƥ�ν���� */
void hospac_des_int(void);			/* �����߶ػ� */
void hospac_ena_int(void);			/* �����ߵ��� */
void hospac_cre_cnt_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* �¹ԥ���ƥ����Ȥκ���(������֥���) */
#define hospac_cre_cnt(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_cnt_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf);
													/* ������֥�¦���Թ礬�����褦�˰����������ؤ� */
void hospac_swi_cnt(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* �¹ԥ���ƥ����Ȥ����� */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* �㳰�����¹����� */


/* ------------------------------------------ */
/*               �ޥ������                   */
/* ------------------------------------------ */

#define hospac_del_cnt(pk_ctxinf)			/* �¹ԥ���ƥ����Ȥκ�� */
/* H8 �Ǥϥ���ƥ����Ⱥ������������ */



#endif	/* __HOS4_hospac_h8_300_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
