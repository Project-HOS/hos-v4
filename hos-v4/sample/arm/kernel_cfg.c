/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ륳��ե�����졼����� �������ե�����                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"

/* INCLUDE() API �ˤ������ */
#include "test.h"



/* ------------------------------------------ */
/*         ��ǥ����塼����Ū����             */
/* ------------------------------------------ */

T_MKNL_QUE mknl_rdq_tbl[8];			/* ��ǥ������塼�ơ��֥� */
const INT mknl_rdq_cnt = 8;			/* ��ǥ������塼�Ŀ� */



/* ------------------------------------------ */
/*             ����������Ū����               */
/* ------------------------------------------ */

static UW Tsk1Stack[(4096 + 3) / 4];
static UW Tsk2Stack[(4096 + 3) / 4];
static UW Tsk3Stack[(4096 + 3) / 4];

/* ����������ȥ���֥�å��ơ��֥�(ROM��) */
const T_KERNEL_TCB_ROM kernel_tcb_rom[3] =
	{
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task1, (PRI)1, (SIZE)sizeof(Tsk1Stack), (VP)Tsk1Stack},
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task2, (PRI)2, (SIZE)sizeof(Tsk2Stack), (VP)Tsk2Stack},
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task3, (PRI)3, (SIZE)sizeof(Tsk3Stack), (VP)Tsk3Stack},
	};

/* ����������ȥ���֥�å��ơ��֥�(RAM��) */
T_KERNEL_TCB_RAM kernel_tcb_ram[3];

/* ����������ȥ���֥�å��ơ��֥�(RAM��) */
T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[3] =
	{
		&kernel_tcb_ram[0],
		&kernel_tcb_ram[1],
		&kernel_tcb_ram[2],
	};

const INT kernel_tcb_cnt = 3;					/* ����������ȥ���֥�å��Ŀ� */



/* ------------------------------------------ */
/*            ���ޥե�����Ū����              */
/* ------------------------------------------ */

const T_KERNEL_SEMCB_ROM kernel_semcb_rom[2] =	/* ���ޥե�����ȥ���֥�å�(ROM��) */
	{
		{TA_TFIFO, 1, 1},
		{TA_TFIFO, 1, 1},
	};

T_KERNEL_SEMCB_RAM kernel_semcb_ram[2];			/* ���ޥե�����ȥ���֥�å�(RAM��) */

/* ���ޥե�����ȥ���֥�å��ơ��֥�(RAM��) */
T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[2] =
	{
		&kernel_semcb_ram[0],
		&kernel_semcb_ram[1],
	};

const INT kernel_semcb_cnt = 2;					/* ���ޥե�����ȥ���֥�å��Ŀ� */



/* ------------------------------------------ */
/*        ���٥�ȥե饰����Ū����            */
/* ------------------------------------------ */
const T_KERNEL_FLGCB_ROM kernel_flgcb_rom[2] =	/* ���٥�ȥե饰����ȥ���֥�å�(ROM��) */
	{
		{TA_WSGL, 0},
		{TA_WSGL, 0},
	};

T_KERNEL_FLGCB_RAM kernel_flgcb_ram[2];			/* ���٥�ȥե饰����ȥ���֥�å�(RAM��) */

T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[2] =	/* ���٥�ȥե饰����ȥ���֥�å��ơ��֥�(RAM��) */
	{
		&kernel_flgcb_ram[0],
		&kernel_flgcb_ram[1],
	};

const INT kernel_flgcb_cnt = 2;					/* ���٥�ȥե饰����ȥ���֥�å��Ŀ� */



/* ------------------------------------------ */
/*         �ǡ������塼����Ū����             */
/* ------------------------------------------ */
VP_INT kernel_dtq1data[128];
VP_INT kernel_dtq2data[128];

const T_KERNEL_DTQCB_ROM kernel_dtqcb_rom[2] =	/* ���٥�ȥե饰����ȥ���֥�å�(ROM��) */
	{
		{0, 128, kernel_dtq1data},
		{0, 128, kernel_dtq2data},
	};

T_KERNEL_DTQCB_RAM kernel_dtqcb_ram[2];			/* ���٥�ȥե饰����ȥ���֥�å�(RAM��) */

T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[2] =	/* ���٥�ȥե饰����ȥ���֥�å��ơ��֥�(RAM��) */
	{
		&kernel_dtqcb_ram[0],
		&kernel_dtqcb_ram[1],
	};

const INT kernel_dtqcb_cnt = 2;					/* ���٥�ȥե饰����ȥ���֥�å��Ŀ� */



/* ------------------------------------------ */
/*          ���ִ�����ǽ����Ū����            */
/* ------------------------------------------ */

const UW kernel_tic_deno = TIC_DENO;			/* TIC_DENO ������ */
const UW kernel_tic_div  = TIC_NUME / TIC_DENO;	/* �١����û�ñ�̤����� */
const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;	/* �����û��̤����� */

T_MKNL_TIMOUT mknl_timout[16];					/* �����ॢ�����Ԥ����� */
const INT     mknl_timout_size = 16;			/* �����ॢ�����Ԥ�����Υ����� */



/* ------------------------------------------ */
/*          �����ϥ�ɥ����Ū����            */
/* ------------------------------------------ */

T_KERNEL_CYCCB_ROM kernel_cyccb_rom[1] =		/* �����ϥ�ɥ饳��ȥ���֥�å�(ROM��) */
	{
		{0, CycHandler1, 10},
	};

T_KERNEL_CYCCB_RAM kernel_cyccb_ram[1];			/* �����ϥ�ɥ饳��ȥ���֥�å�(RAM��) */

T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[1] =	/* �����ϥ�ɥ饳��ȥ���֥�å��ơ��֥� */
	{
		&kernel_cyccb_ram[0],
	};

const INT kernel_cyccb_cnt = 1;					/* �����ϥ�ɥ饳��ȥ���֥�å��Ŀ� */



/* ------------------------------------------ */
/*               ����������                 */
/* ------------------------------------------ */

UW mknl_int_stack[(1024 + 3) / 4];				/* �������ѥ����å� */

const VP   mknl_int_stk   = mknl_int_stack;		/* �����ߥ����å����ɥ쥹 */
const SIZE mknl_int_stksz = 1024;				/* �����ߥ����å������� */

T_KERNEL_INTCB  kernel_intcb_tbl[32];			/* �����ߴ�������ȥ���֥�å��ơ��֥� */
const INT       kernel_intcb_cnt = 32;			/* ����������ֹ�� */



/* ------------------------------------------ */
/*               ������ؿ�                   */
/* ------------------------------------------ */

/* ����ե�����졼�����ѿ��ν���� */
void kernel_cfg_init(void)
{
	/* RAM�ǡ������ؤ�0�ʤΤ� DATA �ΰ���֤���� BSS ���֤��Ƥ����ǽ���������ۤ�����Ψ���褤 */

	/* ����������ȥ���֥�å������ */
	kernel_tcb_ram[0].tcbrom = &kernel_tcb_rom[0];
	kernel_tcb_ram[1].tcbrom = &kernel_tcb_rom[1];
	kernel_tcb_ram[2].tcbrom = &kernel_tcb_rom[2];

	/* ���ޥե�����ȥ���֥�å������ */
	kernel_semcb_ram[0].semcbrom = &kernel_semcb_rom[0];
	kernel_semcb_ram[1].semcbrom = &kernel_semcb_rom[1];

	/* ���٥�ȥե饰����ȥ���֥�å������ */
	kernel_flgcb_ram[0].flgcbrom = &kernel_flgcb_rom[0];
	kernel_flgcb_ram[1].flgcbrom = &kernel_flgcb_rom[1];
	
	/* �ǡ������塼����ȥ���֥�å������ */
	kernel_dtqcb_ram[0].dtqcbrom = &kernel_dtqcb_rom[0];
	kernel_dtqcb_ram[1].dtqcbrom = &kernel_dtqcb_rom[1];
	
	/* �����ϥ�ɥ饳��ȥ���֥�å������ */
	kernel_cyccb_ram[0].cyccbrom = &kernel_cyccb_rom[0];

	/* ��������Ͽ */
	kernel_intcb_tbl[1].exinf = 0;
	kernel_intcb_tbl[1].isr   = IntHndler1;
}


/* ATT_INI �ʤɤ���� */
void kernel_cfg_start(void)
{
	/* ���Ѥ��륪�֥������ȤΤߤ�����(;�פʤ�Τ��󥯤����ʤ�) */
	kernel_ini_tsk();		/* �������ν���� */
	kernel_ini_sem();		/* ���ޥե��ν���� */
	kernel_ini_flg();		/* ���٥�ȥե饰�ν���� */

	/* ATT_INI �ν��� */
	TestStart((VP_INT)0);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
