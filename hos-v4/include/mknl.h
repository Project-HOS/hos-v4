/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ��¸��������إå�                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__mknl_h__
#define __HOS_V4__mknl_h__



#include "itron.h"
#include "hosdenv.h"



/* ------------------------------------------ */
/*                ������                    */
/* ------------------------------------------ */

/* ������ͥ���٤��ϰ� */
#define TMIN_TPRI			1					/* ������ͥ���٤κǾ��� */
#define TMAX_TPRI			(TMIN_TPRI + mknl_rdq_cnt - 1)
												/* ������ͥ���٤κ����� */


/* �����ƥ�ξ��� */
#define MKNL_TSS_TSK		0x00				/* ���������¹��� */
#define MKNL_TSS_INDP		0x04				/* ��������Ω���¹��� */
#define MKNL_TSS_DDSP		0x01				/* �ǥ����ѥå��ػ� (dis_dsp ͭ��) */
#define MKNL_TSS_DINT		0x02				/* �����߶ػ�(loc_cpu ͭ��) */
#define MKNL_TSS_DDLY		0x80				/* �ǥ����ѥå��ٱ��� */

/* ���������㳰�������� */
#define MKNL_TTS_RDLY		0x01				/* �㳰������α���� */
#define MKNL_TTS_DRAS		0x02				/* �㳰�����ػ߾��� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ���塼�����֥��å� */
typedef struct t_mknl_que
{
	struct t_mknl_tcb *head;	/* ���塼����Ƭ */
} T_MKNL_QUE;


/* �̥����ͥ� ����������ȥ�����֥��å� */
typedef struct t_mknl_tcb
{
	T_HOSPAC_CTXINF   ctxinf;		/* ����ƥ����Ⱦ�����¸�֥��å� */
	unsigned int      tskwait : 16;	/* �Ԥ��װ� */
	unsigned int      tskpri  : 8;	/* ���ߤ�ͥ���� */
	unsigned int      tskstat : 6;	/* �������ξ��� */
	unsigned int      texstat : 2;	/* �㳰�����ξ��� */
	ER_UINT           ercd;			/* �Ԥ�����װ��ѥ��顼������ */
	VP_INT            data;			/* ���ѥǡ����ΰ� */
	struct t_mknl_que *que;			/* °���Ƥ��륭�塼  */
	struct t_mknl_tcb *next;		/* ���塼�Ǥμ���TCB */
	struct t_mknl_tcb *prev;		/* ���塼�Ǥ�����TCB */
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
extern T_MKNL_TCB      *mknl_run_mtcb;		/* �¹��楿��������ȥ�����֥��å� */
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

/* �̥����ͥ�Υ����ӥ�������ϸ�§ mknl_sys_loc() �� */
/* ���å����줿���֤ǸƤӽФ���뤳��                 */

/* �����ƥ����� */
void    mknl_ini_sys(void);									/* �̥����ͥ륷���ƥ�ν���� */
void    mknl_sta_startup(void);								/* �������ȥ��åץ롼����γ��Ͻ��� */
void    mknl_ext_startup(void);								/* �������ȥ��åץ롼����ν�λ���� */


/* ���������� */
#define mknl_ini_tsk(mtcb)	do { (mtcb)->tskstat = TTS_DMT; } while (0)
															/* �������ν����(�ޥ����ؿ�) */
void    mknl_sta_tsk(T_MKNL_TCB *mtcb, VP_INT exinf,
							FP task, PRI tskpri,
							SIZE stksz, VP stk);			/* �������γ��� */
void    mknl_ext_tsk(T_MKNL_TCB *mtcb);						/* �������ν�λ */
void    mknl_chg_pri(T_MKNL_TCB *mtcb, PRI tskpri);			/* ������ͥ�����ѹ� */
void    mknl_wai_tsk(T_MKNL_TCB *mtcb, STAT tskwait);		/* ���������Ԥ� */
void    mknl_wup_tsk(T_MKNL_TCB *mtcb, ER_UINT ercd);		/* ���������Ԥ���� */
void    mknl_sus_tsk(T_MKNL_TCB *mtcb);						/* �������ζ����Ԥ� */
void    mknl_rsm_tsk(T_MKNL_TCB *mtcb);						/* �������ζ����Ԥ���� */
void    mknl_rot_rdq(PRI tskpri);							/* ������ͥ���̤β�ž */
ER_UINT mknl_exe_dsp(void);									/* �������ǥ����ѥå��μ¹� */
void    mknl_dly_dsp(void);									/* �ٱ䤷�Ƥ����ǥ����ѥå��μ¹� */
T_MKNL_TCB* mknl_srh_top(void);								/* ��ǥ������塼��Ƭ�Υ�������õ�� */
#define mknl_get_run_tsk()		(mknl_run_mtcb)				/* �¹��楿�����μ���(�ޥ����ؿ�) */
#define mknl_get_pri(mtcb)		((PRI)(mtcb)->tskpri)		/* ������ͥ���ټ���(�ޥ����ؿ�) */
#define mknl_get_tskstat(mtcb)	((STAT)(mtcb)->tskstat)		/* ���������ּ���(�ޥ����ؿ�) */
#define mknl_get_tskwait(mtcb)	((STAT)(mtcb)->tskwait)		/* �Ԥ��װ�����(�ޥ����ؿ�) */

void    kernel_task_entry(VP_INT exinf);					/* �������Υ���ȥ꡼�ݥ����(�����ͥ�¦���Ѱդ��뤳��) */


/* �������㳰���� */
void    mknl_ras_tex(T_MKNL_TCB *mtcb);						/* �������㳰�������׵� */
void    mknl_exe_tex(void);									/* �������㳰�����μ¹� */
#define mknl_dis_tex(mtcb)	\
	do { (mtcb)->texstat |= MKNL_TTS_DRAS; } while (0)		/* �������㳰�����ζػ� */
#define mknl_ena_tex(mtcb)	\
	do { (mtcb)->texstat &= ~MKNL_TTS_DRAS; } while (0)		/* �������㳰�����ε��� */
#define mknl_sns_tex()	\
	((mknl_run_mtcb == NULL || (mknl_run_mtcb->texstat & MKNL_TTS_DRAS)) ? TRUE: FALSE)
															/* �������㳰�����ػ߾��֤λ��� */

void    kernel_tex_entry(void);								/* �������㳰��������ȥ꡼�ݥ����(�����ͥ�¦���Ѱդ��뤳��) */
	

/* �����ƥ����� */
#define mknl_loc_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_dis_int(); } } while (0)
															/* �����ƥ�Υ��å�(�ޥ����ؿ�) */
#define mknl_unl_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_ena_int(); } } while (0)
															/* �����ƥ�Υ��å����(�ޥ����ؿ�) */
#define mknl_dis_int()	do { hospac_dis_int(); } while (0)	/* �����߶ػ� */
#define mknl_ena_int()	do { hospac_ena_int(); } while (0)	/* �����ߵ��� */
#define mknl_sta_ind()	do { mknl_ctx_stat |= MKNL_TSS_INDP; } while (0)
															/* �󥿥������γ���(�ޥ����ؿ�) */
#define mknl_ext_ind()	do { mknl_ctx_stat &= ~MKNL_TSS_INDP; } while (0)
															/* �󥿥������ν�λ(�ޥ����ؿ�) */
#define mknl_loc_cpu()	do { mknl_ctx_stat |= MKNL_TSS_DINT; } while (0)
															/* CPU�Υ��å�(�ޥ����ؿ�) */
#define mknl_unl_cpu()	do { mknl_ctx_stat &= ~MKNL_TSS_DINT; } while (0)
															/* CPU�Υ��å����(�ޥ����ؿ�) */
#define mknl_dis_dsp()	do { mknl_ctx_stat |= MKNL_TSS_DDSP; } while (0)
															/* �ǥ����ѥå��ζػ�(�ޥ����ؿ�) */
#define mknl_ena_dsp()	do { mknl_ctx_stat &= ~MKNL_TSS_DINT; } while (0)
															/* �ǥ����ѥå��ε���(�ޥ����ؿ�) */
#define mknl_sns_ctx()	((mknl_ctx_stat & MKNL_TSS_INDP) ? TRUE : FALSE)
															/* ����ƥ����Ȥλ���(�ޥ����ؿ�) */
#define mknl_sns_loc()	((mknl_ctx_stat & MKNL_TSS_DINT) ? TRUE : FALSE)
															/* CPU���å����֤λ���(�ޥ����ؿ�) */
#define mknl_sns_dsp()	((mknl_ctx_stat & MKNL_TSS_DDSP) ? TRUE : FALSE)
															/* �ǥ����ѥå��ػ߾��֤λ���(�ޥ����ؿ�) */
#define mknl_sns_dpn()	((mknl_ctx_stat & MKNL_TSS_DDLY) ? TRUE : FALSE)
															/* �ǥ����ѥå���α���֤λ���(�ޥ����ؿ�) */
#define mknl_sns_wai()	((mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT)) ? TRUE : FALSE)
															/* �Ԥ����ְܹԲ�ǽ����(�ޥ����ؿ�) */


/* ���塼��� */
#define mknl_ini_que(que)	do { (que)->head = NULL; } while (0)
															/* ���塼�ν���� */
void    mknl_add_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* ��������FIFO��ǥ��塼���ɲ� */
void    mknl_adp_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* ��������ͥ���ٽ�ǥ��塼���ɲ� */
void    mknl_rmv_que(T_MKNL_TCB *mtcb);						/* �������򥭥塼��������� */
void    mknl_rot_que(T_MKNL_QUE *que);						/* ��ǥ������塼�β�ž */
#define mknl_ref_qhd(que)	((que)->head)					/* ���塼����Ƭ�������λ���(�ޥ����ؿ�) */
#define mknl_ref_nxt(que, mtcb)		\
		((mtcb)->next != (que)->head ? (que)->head : NULL)	/* ���Υ��塼����� */

/* �����ॢ�����Ԥ����� */
void    mknl_tic_tmout(RELTIM tictim);						/* �����ॢ���Ȥ˥�����ƥ��å����� */
ER      mknl_add_tmout(T_MKNL_TCB *mtcb, RELTIM tmout);		/* �����ॢ�����Ԥ�����˥��������ɲ� */
void    mknl_rmv_tmout(T_MKNL_TCB *mtcb);					/* �����ॢ�����Ԥ����󤫤饿����������� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__mknl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */