/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_tsk.h"
#include "knl_mem.h"



/* ������������(�����ͥ�����) */
ER kernel_cre_tsk(
		ID           tskid,		/* �����оݤΥ�����ID�ֹ� */
		const T_CTSK *pk_ctsk)	/* ������������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_KERNEL_TCB_ROM *tcb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* ɬ�פʥ��ꥵ������׻� */
	memsize = sizeof(T_KERNEL_TCB_RAM) + sizeof(T_KERNEL_TCB_ROM);
	if ( pk_ctsk->stk == NULL )
	{
		memsize += pk_ctsk->stksz;	/* �����å���������û� */
	}
	
	/* ������� */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
#endif

	/* �ݥ������� */	
	tcb_ram  = (T_KERNEL_TCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_TCB_RAM);
	tcb_rom  = (T_KERNEL_TCB_ROM *)memptr;
	if ( pk_ctsk->stk == NULL )
	{
		memptr  += sizeof(T_KERNEL_TCB_ROM);
		tcb_rom->stk = (VP)memptr;
	}
	else
	{
		tcb_rom->stk = pk_ctsk->stk;
	}

	/* �̥����ͥ륿�����ν���� */
	memset(&tcb_ram->mtcb, 0, sizeof(tcb_ram->mtcb));
	mknl_ini_tsk(&tcb_ram->mtcb);

	/* ������ */
	tcb_ram->actcnt  = 0;					/* ��ư�׵ᥭ�塼���󥰿� */
	tcb_ram->suscnt  = 0;					/* SUSPEND�׵�ͥ��ȿ� */
	tcb_ram->wupcnt  = 0;					/* �����׵ᥭ�塼���󥰿� */
	tcb_ram->tcb_rom = tcb_rom;				/* ����������ȥ���֥�å�ROM���ؤΥݥ��� */
	tcb_rom->tskatr  = pk_ctsk->tskatr;		/* ������°�� */
	tcb_rom->exinf   = pk_ctsk->exinf;		/* �������γ�ĥ���� */
	tcb_rom->task    = pk_ctsk->task;		/* �������ε�ư���� */
	tcb_rom->itskpri = pk_ctsk->itskpri;	/* �������ε�ư��ͥ���� */
	tcb_rom->stksz   = pk_ctsk->stksz;		/* �������Υ����å��Υ������ʥХ��ȿ��� */

	/* ����������ȥ���֥�å��ơ��֥����Ͽ */
	kernel_tcb_ram_tbl[tskid - KERNEL_TMIN_TSKID] = tcb_ram;

	/* �¹Ծ��֤����� */
	if ( pk_ctsk->tskatr & TA_ACT )
	{
		/* �¹ԥ���ƥ�������Ͽ */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* ��Ͽ���륿���� */
				tcb_rom->exinf,			/* �������γ�ĥ���� */
				(FP)kernel_task_entry,	/* �������ε�ư���� */
				tcb_rom->itskpri,		/* �������ε�ư��ͥ���� */
				tcb_rom->stksz,			/* �������Υ����å��ΰ襵���� */
				tcb_rom->stk			/* �������Υ����å��ΰ����Ƭ���� */
			);	
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
