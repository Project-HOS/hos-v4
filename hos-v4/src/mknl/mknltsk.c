/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"
#include "kernel.h"



/* �������γ��� */
void mknl_sta_tsk(
		T_MKNL_TCB *mtcb,					/* �̥����ͥ륿��������ȥ���֥�å� */
		VP_INT     exinf,					/* �������γ�ĥ���� */
		FP         task,					/* �������ε�ư���� */
		PRI        tskpri,					/* �������ε�ư��ͥ���� */
		SIZE       stksz,					/* �������Υ����å��ΰ�Υ����� */
		VP         stk)						/* �������Υ����å��ΰ����Ƭ���� */
{
	/* �¹ԥ���ƥ����Ȥκ��� */
	mtcb->data = exinf;
	hospac_cre_ctx(&mtcb->ctxinf, exinf, task, stksz, stk);

	/* �������ξ������� */
	mtcb->tskstat = TTS_RDY;	/* ��ǥ������֤����� */
	mtcb->texstat = 0;			/* �㳰���ֽ���� */
	mtcb->tskpri  = tskpri;		/* ͥ�������� */
	mtcb->tskwait = 0;			/* �Ԥ��װ������ */

	/* ��ǥ������塼������ */
	mknl_add_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
}


/* �������ν�λ */
void mknl_ext_tsk(
				T_MKNL_TCB *mtcb)	/* ��λ�����륿���� */
{
	/* �����ॢ���ȥ��塼�ˤ���к�� */
	mknl_del_tmout(mtcb);		

	/* ���������塼���鳰�� */
	if ( mtcb->que != NULL )
	{
		mknl_del_que(mtcb);
	}

	mtcb->tskstat = TTS_DMT;	/* �ٻ߾��֤����� */
	mtcb->tskwait = 0;			/* �Ԥ��װ����ꥢ */

	/* �¹ԥ���ƥ����Ȥκ�� */
	hospac_del_ctx(&mtcb->ctxinf);
}



/* ������ͥ�����ѹ� */
void mknl_chg_pri(
				T_MKNL_TCB *mtcb,	/* ͥ���٤��ѹ����륿���� */
				PRI tskpri)			/* ���ꤹ��ͥ���� */
{
	/* ͥ�����ѹ� */
	if ( !(mtcb->tskstat & TTS_WAI) )
	{
		/* �Ԥ����֤Ǥʤ���Х�ǥ������塼�˷Ҥ��ʤ��� */
		mknl_del_que(mtcb);
		mknl_add_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
	}
	mtcb->tskpri = tskpri;
}


/* ���������Ԥ����� */
void mknl_wai_tsk(
		T_MKNL_TCB *mtcb,		/* �Ԥ����֤ˤ��륿���� */
		STAT        tskwait)	/* �Ԥ��װ� */
{
	/* �Ԥ����֤����� */
	mknl_del_que(mtcb);		/* ��ǥ������塼���鳰�� */
	mtcb->tskstat = TTS_WAI;
	mtcb->tskwait = tskwait;
}


/* ���������Ԥ���� */
void mknl_wup_tsk(
		T_MKNL_TCB *mtcb,	/* ���꡼�ײ�����륿���� */
		ER_UINT    ercd)	/* ������륿�������Ϥ����顼������ */
{
	/* �������Υ��꡼�ײ�� */
	mtcb->ercd = ercd;
	mknl_add_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_RDY;	/* �Ԥ�����ʤ�¹Բ�ǽ���� */
	}
	else
	{
		mtcb->tskstat = TTS_SUS;	/* ����Ԥ����֤ʤ鶯���Ԥ����� */
	}
	mtcb->tskwait = 0;		/* �Ԥ��װ����ꥢ */
}


/* �������ζ����Ԥ� */
void mknl_sus_tsk(
		T_MKNL_TCB *mtcb)	/* �����Ԥ����֤ˤ��륿���� */
{
	/* �������ζ����Ԥ�(��ǥ������塼����ϳ����ʤ�) */
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_WAS;
	}
	else
	{
		mtcb->tskstat = TTS_SUS;
	}
}


/* �������ζ����Ԥ���� */
void mknl_rsm_tsk(
		T_MKNL_TCB *mtcb)	/* �����Ԥ�������륿���� */
{
	/* �����Ԥ���� */
	if ( mtcb->tskstat == TTS_WAS )
	{
		mtcb->tskstat = TTS_WAI;		/* ����Ԥ����֤ʤ��Ԥ����� */
	}
	else
	{
		mtcb->tskstat = TTS_RDY;		/* �����Ԥ����֤ʤ�¹Բ�ǽ���� */
	}
}


/* �������ǥ����ѥå��μ¹� */
ER_UINT mknl_exe_dsp(void)
{
	T_HOSPAC_CTXINF *ctxinf_top;
	T_HOSPAC_CTXINF *ctxinf_run;
	T_MKNL_TCB *mtcb_top;
	T_MKNL_TCB *mtcb_run;

	/* ����ƥ����ȥ����å� */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP) )
	{
		/* �ǥ����ѥå��¹Բ�ǽ���֤�̵�������α���� */
		mknl_ctx_stat |= MKNL_TSS_DDLY;	/* �ǥ����ѥå��ٱ�ե饰�򥻥å� */
		return E_OK;
	}

	/* �ǹ�ͥ���٤μ¹Բ�ǽ��������õ�� */
	mtcb_top = mknl_srh_top();

	mtcb_run = mknl_run_mtcb;	/* ���ߤΥ����������������� */

	/* �¹��楿������Ʊ���ʤ鲿�⤷�ʤ�(�����ɥ뤫�饢���ɥ��ޤ�� */
	if ( mtcb_top == mtcb_run )
	{
		if ( mtcb_run == NULL )
		{
			return E_OK;
		}
		return mtcb_run->ercd;
	}

	/* �����ɥ륿�����¹���Ǥʤ��������å� */
	if ( mtcb_run == NULL )
	{
		/* �����ɥ�ʤ饢���ɥ륳��ƥ����Ȥ����� */
		ctxinf_run = &mknl_idlctx;
	}
	else
	{
		/* �¹���Υ���ƥ����Ȥ����� */
		ctxinf_run = &mtcb_run->ctxinf;
	}

	/* ���˼¹Ԥ��륿���������뤫�ɤ��������å� */
	if ( mtcb_top == NULL )
	{
		/* �¹��褬̵����Х����ɥ륳��ƥ����Ȥ����� */
		mknl_run_mtcb = NULL;
		ctxinf_top    = &mknl_idlctx;
	}
	else
	{
		/* �¹���Υ�������¹��楿�����Ȥ�����Ͽ */
		mknl_run_mtcb     = mtcb_top;
		mtcb_top->tskstat = TTS_RDY;
		
		/* �¹���Υ���ƥ����Ȥ����� */
		ctxinf_top = &mtcb_top->ctxinf;
	}

	/* ����������ƥ����ȥ����å��¹� */
	hospac_swi_ctx(ctxinf_run, ctxinf_top);

	if ( mtcb_run == NULL )
	{
		return E_OK;
	}

	return mtcb_run->ercd;
}



/* �ٱ䤷�Ƥ����ǥ����ѥå��μ¹� */
void mknl_dly_dsp(void)
{
	/* �����ƥॳ��ƥ����ȥ����å� */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP) )
	{
		return;		/* �ǥ����ѥå��¹Բ�ǽ�Ǥʤ������α³�� */
	}

	/* �ٱ�ե饰�����å� */
	if ( !(mknl_ctx_stat & MKNL_TSS_DDLY) )
	{
		return;		/* �ٱ䤬̵����в��⤷�ʤ� */
	}

	/* �ٱ�ե饰���ꥢ */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* �ٱ�ǥ����ѥå��¹� */
	mknl_exe_dsp();
}


/* ��ǥ������塼��Ƭ�Υ�������õ�� */
T_MKNL_TCB* mknl_srh_top(void)
{
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_head;
	INT i;

	/* �ǹ�ͥ���٤μ¹Բ�ǽ��������õ�� */
	for ( i = 0; i < mknl_rdq_cnt; i++ )	/* ͥ���٤ι⤤���塼�����˸��� */
	{
		if ( mknl_rdq_tbl[i].head != NULL )
		{
			/* �����Ԥ����֤�̵����Ƭ��������õ�� */
			mtcb_head = mknl_rdq_tbl[i].head;
			mtcb      = mtcb_head;
			do
			{
				if ( !(mtcb->tskstat & TTS_SUS) )
				{
					return mtcb;	/* ���Ĥ������������֤� */
				}
				mtcb = mtcb->next;
			} while ( mtcb != mtcb_head);
		}
	}

	return NULL;	/* �¹Բ�ǽ������̵�� */
}


/* ������ͥ���̤β�ž */
void mknl_rot_rdq(
		PRI tskpri)		/* ͥ���̤��ž�����оݤ�ͥ���� */
{
	mknl_rot_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI]);
}



/* �������㳰�������׵� */
void mknl_ras_tex(
		T_MKNL_TCB *mtcb)	/* �㳰�������׵᤹�륿���� */
{
	if ( mtcb == mknl_run_mtcb && !(mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* �¹��楿�����ǡ��㳰�ػߤǤʤ�����㳰ȯ�� */
		do
		{
			mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mtcb->texstat != 0 );	/* �㳰�װ����ʤ��ʤ�ޤǥ롼�� */
	}
	else
	{
		/* �㳰����α���� */
		mtcb->texstat &= MKNL_TTS_RDLY;
	}
}


/* �������㳰�����μ¹� */
void mknl_exe_tex(void)
{
	if (  (mknl_run_mtcb->texstat & MKNL_TTS_RDLY)
				&& !(mknl_run_mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* �㳰��α�����ꡢ�㳰�ػߤǤʤ�����㳰ȯ�� */
		do
		{
			mknl_run_mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mknl_run_mtcb->texstat != 0 );	/* �㳰�װ����ʤ��ʤ�ޤǥ롼�� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
