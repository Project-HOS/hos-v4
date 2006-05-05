/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� �����ƥ����� �����ƥॿ�����¹�                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"


static void mknl_exe_sys_start(VP_INT exinf);	/* �����ƥॿ�����μ¹� */

static FP mknl_exe_sys_exec;					/* �����ƥ�¹����� */


/* �����ƥ�¹�  */
void mknl_exe_sys(
		FP     exec,
		VP_INT exinf)
{
	T_HOSPAC_CTXINF *ctxinf_run;
	
	/* �¹��楳��ƥ����Ȥ����� */
	ctxinf_run = &mknl_run_mtcb->ctxinf;
	
	/* �����ƥ�¹�������¸ */
	mknl_exe_sys_exec = exec;
	
	/* �����ɥ륳��ƥ����Ȥ򥷥��ƥॿ�����Ȥ��ư������ */
	hospac_del_ctx(&mknl_idlctx);												/* �����ɥ륳��ƥ����Ȥ��˴� */
	hospac_cre_ctx(&mknl_idlctx, exinf, exec, mknl_idl_stksz, mknl_idl_stk);	/* �����ɥ륿�������� */
	
	/* ����������ƥ����ȥ����å��¹� */
	mknl_run_mtcb = NULL;
	hospac_swi_ctx(ctxinf_run, &mknl_idlctx);
}


/* �����ƥॿ�����μ¹� */
void mknl_exe_sys_start(VP_INT exinf)
{
	/* �����ƥॿ�����Ǽ¹� */
	mknl_exe_sys_exec(exinf);
	
	/* ��λ�奢���ɥ����� */
	mknl_idl_loop();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
