/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"
#include "dsp_hok.h"


/* �������ǥ����ѥå��μ¹� */
ER_UINT mknl_exe_dsp(void)
{
	T_HOSPAC_CTXINF *ctxinf_top;
	T_HOSPAC_CTXINF *ctxinf_run;
	T_MKNL_TCB *mtcb_top;
	T_MKNL_TCB *mtcb_run;

	/* ����ƥ����ȥ����å� */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT) )
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

	_HOS_TSW_HOK();		/* ����ƥ����ȥ����å��Υեå� */

	if ( mtcb_run == NULL )
	{
		return E_OK;
	}

	return mtcb_run->ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
