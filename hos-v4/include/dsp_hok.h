/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ǥХå��ٱ�  �ǥ����ѥå��եå�                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__dsp_hok_h__
#define __HOS_V4__dsp_hok_h__



/* �ǥ����ѥå��եå��ޥ��� */
#ifdef _HOS_DSP_HOK_ENABLE
#ifndef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK_ENABLE
#endif
#ifndef _HOS_INT_HOK_ENABLE
#define _HOS_INT_HOK_ENABLE
#endif
#endif

/* �����������å� �եå��ޥ������� */
#ifdef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK()	_hos_tsw_hok()	/* ͭ�� */
#else
#define _HOS_TSW_HOK()					/* ̵�� */
#endif

/* ������ �եå��ޥ������� */
#ifdef _HOS_INT_HOK_ENABLE
#define _HOS_INTSTA_HOK(intno)	_hos_intsta_hok(intno)	/* ͭ�� */
#define _HOS_INTEXT_HOK(intno)	_hos_intext_hok(intno)
#else
#define _HOS_INTSTA_HOK(intno)							/* ̵�� */
#define _HOS_INTEXT_HOK(intno)
#endif

/* �ǥ����ѥå���������� */
#define _HOS_DSPTYPE_TSKSWC		1	/* �����������å�ȯ�� */
#define _HOS_DSPTYPE_STAINT		2	/* �����߽������� */
#define _HOS_DSPTYPE_EXTINT		3	/* �����߽�����λ */

/* �եå��ޥ��� */
#define _HOS_HOKMSK_TSW			0x01	/* �����������å��եå� */
#define _HOS_HOKMSK_INT			0x02	/* �����ߥեå� */


/* �ǥ����ѥå����� */
typedef struct t_dbg_dspinf
{
	UW  time;		/* ���� */
	INT type;		/* ȯ������ */
	INT id;			/* ID */
} T_DBG_DSPINF;



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ����ؿ� */
void _hosdbg_ini_dsphok(T_DBG_DSPINF dspinf[], INT infcnt);	/* �եå���������� */
void _hosdbg_sta_dsphok(INT mask);							/* �եå��������� */
void _hosdbg_stp_dsphok(void);								/* �եå�������� */

/* ���ɤ߽Ф��ؿ� */
T_DBG_DSPINF *_hosdbg_red_fst(void);		/* �ɤ߽Ф����� */
T_DBG_DSPINF *_hosdbg_red_nxt(void);		/* �����ɤ߽Ф� */

/* �ǥ����ѥå��եå��ؿ� */
void _hos_tsw_hok(void);			/* �����������å� �եå� */
void _hos_intsta_hok(INTNO intno);	/* �����߳��� �եå� */
void _hos_intext_hok(INTNO intno);	/* �����߽�λ �եå� */

/* �桼���������ؿ� */
UW   _hosdbg_get_tim(void);			/* �����ٻ��ּ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__dsp_hok_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
