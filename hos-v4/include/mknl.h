/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ��¸��������إå�                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__mknl_h__
#define __HOS_V4__mknl_h__



#include "itron.h"
#include "hospac.h"


/* ------------------------------------------ */
/*                ������                    */
/* ------------------------------------------ */

/* ������ͥ���٤��ϰ� */
#define TMIN_TPRI		1					/* ������ͥ���٤κǾ��� */
#define TMAX_TPRI		(TMIN_TPRI + mknl_rdq_cnt - 1)
											/* ������ͥ���٤κ����� */


/* �����ƥ�ξ������(HOS�ȼ�) */
#define TSS_TSK			0x00				/* ���������¹��� */
#define TSS_INDP		0x04				/* ��������Ω���¹��� */
#define TSS_DDSP		0x01				/* �ǥ����ѥå��ػ� (dis_dsp ͭ��) */
#define TSS_DINT		0x02				/* �����߶ػ�(loc_cpu ͭ��) */
#define TSS_DDLY		0x80				/* �ǥ����ѥå��ٱ��� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ���塼�����֥�å� */
typedef struct t_mknl_que
{
	struct t_mknl_tcb *head;	/* ���塼����Ƭ */
	INT    tskcnt;				/* ���塼���¤�Ǥ��륿�����ο� */
} T_MKNL_QUE;


/* �̥����ͥ� ����������ȥ���֥�å� */
typedef struct t_mknl_tcb
{
	T_HOSPAC_CTXINF ctxinf;		/* ����ƥ����Ⱦ�����¸�֥�å� */
	STAT    tskwait;			/* �Ԥ��װ� */
	STAT    tskstat;			/* �������ξ��� */
	PRI     tskpri;				/* ���ߤ�ͥ���� */
	ER_UINT ercd;				/* �Ԥ�����װ��ѥ��顼������ */
	VP_INT  data;				/* ���ѥǡ����ΰ� */
	struct t_mknl_que *que;		/* °���Ƥ��륭�塼  */
	struct t_mknl_tcb *next;	/* ���塼�Ǥμ���TCB */
	struct t_mknl_tcb *prev;	/* ���塼�Ǥ�����TCB */
} T_MKNL_TCB;


/* �����ॢ���ȴ����ѹ�¤�� */
typedef struct t_mknl_timout
{
	T_MKNL_TCB *mtcb;		/* �����ॢ�����Ԥ��Υ����� */
	RELTIM     diftim;		/* ����ľ�����Ԥ��������Ȥλ��ֺ� */
} T_MKNL_TIMOUT;



#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------ */
/*              �����ѿ����                  */
/* ------------------------------------------ */

/* �����ƥ���� */
extern STAT            mknl_ctx_stat;		/* �����ƥ�Υ���ƥ����Ⱦ��� */
extern T_MKNL_TCB      *mknl_run_mtcb;		/* �¹��楿��������ȥ���֥�å� */
extern T_HOSPAC_CTXINF mknl_idlctx;			/* �����ɥ�롼�פΥ���ƥ����� */
extern const VP        mknl_int_stk;		/* �����ߥ����å����ɥ쥹 */
extern const SIZE      mknl_int_stksz;		/* �����ߥ����å������� */

/* ���������� */
extern T_MKNL_QUE      mknl_rdq_tbl[];		/* ��ǥ������塼�ơ��֥� */
extern const INT       mknl_rdq_cnt;		/* ��ǥ������塼�Ŀ� */

extern       INT       mknl_timout_tskcnt;	/* �����ॢ�����Ԥ�����Υ������Ŀ� */

/* �����ॢ���ȴ��� */
extern T_MKNL_TIMOUT   mknl_timout[];		/* �����ॢ�����Ԥ����� */
extern const INT       mknl_timout_size;	/* �����ॢ�����Ԥ�����Υ����� */
extern       INT       mknl_timout_tskcnt;	/* �����ॢ�����Ԥ�����Υ������Ŀ� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* �̥����ͥ�Υ����ӥ�������Ϥ��٤� mknl_sys_loc() �� */
/* ��å����줿���֤ǸƤӽФ���뤳��                   */

/* �����ƥ����� */
void mknl_ini_sys(void);							/* �̥����ͥ륷���ƥ�ν���� */
void mknl_sta_startup(void);						/* �������ȥ��åץ롼����γ��Ͻ��� */
void mknl_ext_startup(void);						/* �������ȥ��åץ롼����ν�λ���� */


/* ���������� */
#define mknl_ini_tsk(mtcb)	do { (mtcb)->tskstat = TTS_DMT; } while (0)
													/* �������ν����(�ޥ���ؿ�) */
void mknl_sta_tsk(T_MKNL_TCB *mtcb, VP_INT exinf,
							FP task, PRI tskpri,
							SIZE stksz, VP stk);	/* �������γ��� */
void    mknl_ext_tsk(T_MKNL_TCB *mtcb);				/* �������ν�λ */
void    mknl_chg_pri(T_MKNL_TCB *mtcb, PRI tskpri);	/* ������ͥ�����ѹ� */
void    mknl_wai_tsk(T_MKNL_TCB *mtcb, STAT tskwait);	/* ���������Ԥ� */
void    mknl_wup_tsk(T_MKNL_TCB *mtcb, ER_UINT ercd);	/* ���������Ԥ���� */
void    mknl_sus_tsk(T_MKNL_TCB *mtcb);				/* �������ζ����Ԥ� */
void    mknl_rsm_tsk(T_MKNL_TCB *mtcb);				/* �������ζ����Ԥ���� */
ER_UINT mknl_exe_dsp(void);							/* �������ǥ����ѥå��μ¹� */
void    mknl_dly_dsp(void);							/* �ٱ䤷�Ƥ����ǥ����ѥå��μ¹� */
T_MKNL_TCB* mknl_srh_top(void);						/* ��ǥ������塼��Ƭ�Υ�������õ�� */
#define mknl_get_run_tsk()		(mknl_run_mtcb)		/* �¹��楿�����μ���(�ޥ���ؿ�) */
#define mknl_get_pri(mtcb)		((mtcb)->tskpri)	/* ������ͥ���ټ���(�ޥ���ؿ�) */
#define mknl_get_tskstat(mtcb)	((mtcb)->tskstat)	/* ���������ּ���(�ޥ���ؿ�) */
#define mknl_get_tskwait(mtcb)	((mtcb)->tskwait)	/* �Ԥ��װ�����(�ޥ���ؿ�) */


/* �����ƥ����� */
#define mknl_loc_sys()	\
	do { if ( !(mknl_ctx_stat & TSS_DINT) ) { hospac_dis_int(); } } while (0)
													/* �����ƥ�Υ�å�(�ޥ���ؿ�) */
#define mknl_unl_sys()	\
	do { if ( !(mknl_ctx_stat & TSS_DINT) ) { hospac_ena_int(); } } while (0)
													/* �����ƥ�Υ�å����(�ޥ���ؿ�) */
#define mknl_dis_int()	do { hospac_dis_int(); } while (0)
#define mknl_ena_int()	
#define mknl_sta_ind()	(mknl_ctx_stat |= TSS_INDP)	/* �󥿥������γ���(�ޥ���ؿ�) */
#define mknl_ext_ind()	(mknl_ctx_stat &= ~TSS_INDP)
													/* �󥿥������ν�λ(�ޥ���ؿ�) */
#define mknl_loc_cpu()	(mknl_ctx_stat |= TSS_DINT)	/* CPU�Υ�å�(�ޥ���ؿ�) */
#define mknl_unl_cpu()	(mknl_ctx_stat &= ~TSS_DINT)
													/* CPU�Υ�å����(�ޥ���ؿ�) */
#define mknl_dis_dsp()	(mknl_ctx_stat |= TSS_DDSP) /* �ǥ����ѥå��ζػ�(�ޥ���ؿ�) */
#define mknl_ena_dsp()	do { mknl_ctx_stat &= ~TSS_DINT; mknl_dly_dsp(); } while (0)
													/* �ǥ����ѥå��ε���(�ޥ���ؿ�) */
#define mknl_sns_ctx()	((mknl_ctx_stat & TSS_INDP) ? TRUE : FALSE)
													/* ����ƥ����Ȥλ���(�ޥ���ؿ�) */
#define mknl_sns_loc()	((mknl_ctx_stat & TSS_DINT) ? TRUE : FALSE)
													/* CPU��å����֤λ���(�ޥ���ؿ�) */
#define mknl_sns_dsp()	((mknl_ctx_stat & TSS_DDSP) ? TRUE : FALSE)
													/* �ǥ����ѥå��ػ߾��֤λ���(�ޥ���ؿ�) */
#define mknl_sns_dpn()	((mknl_ctx_stat & TSS_DDLY) ? TRUE : FALSE)
													/* �ǥ����ѥå���α���֤λ���(�ޥ���ؿ�) */
#define mknl_sns_wai()	((mknl_ctx_stat & (TSS_INDP | TSS_DDSP)) ? TRUE : FALSE)
													/* �Ԥ����ְܹԲ�ǽ����(�ޥ���ؿ�) */

/* ���塼��� */
void mknl_add_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);		/* ��������FIFO��ǥ��塼���ɲ� */
void mknl_adp_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);		/* ��������ͥ���ٽ�ǥ��塼���ɲ� */
void mknl_del_que(T_MKNL_TCB *mtcb);						/* �������򥭥塼������ */
void mknl_rot_que(T_MKNL_QUE *que);							/* ��ǥ������塼�β�ž */
#define mknl_ref_qhd(que)	((que)->head)					/* ���塼����Ƭ�������λ���(�ޥ���ؿ�) */


/* �����ॢ�����Ԥ����� */
void mknl_tic_tmout(RELTIM tictim);							/* �����ॢ���Ȥ˥�����ƥ��å����� */
ER   mknl_add_tmout(T_MKNL_TCB *mtcb, RELTIM tmout);		/* �����ॢ�����Ԥ�����˥��������ɲ� */
void mknl_del_tmout(T_MKNL_TCB *mtcb);						/* �����ॢ�����Ԥ����󤫤饿�������� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__mknl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
