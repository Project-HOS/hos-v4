/* ------------------------------------------------------------------------ */
/*  HOS-V4  kernel configuration                                            */
/*    kernel object create and initialize                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"

#include "sample.h"
#include "ostimer.h"
#include "v850es/vect.h"



/* ------------------------------------------ */
/*                 idle stack                 */
/* ------------------------------------------ */

VP         mknl_idl_stkblk[((1024) + sizeof(VP) - 1) / sizeof(VP)];	/* idle stack block*/
const VP   mknl_idl_stk   = (VP)(mknl_idl_stkblk);	/* idle stack */
const SIZE mknl_idl_stksz = (SIZE)sizeof(mknl_idl_stkblk);	/* idle stack size */



/* ------------------------------------------ */
/*           create ready queue               */
/* ------------------------------------------ */

T_MKNL_QUE mknl_rdq_tbl[8];
const INT  mknl_rdq_cnt = 8;



/* ------------------------------------------ */
/*             interrupt stack                */
/* ------------------------------------------ */

VP         kernel_int_stkblk[((1024) + sizeof(VP) - 1) / sizeof(VP)];	/* interrupt stack block*/
const VP   kernel_int_sp  = &kernel_int_stkblk[sizeof(kernel_int_stkblk) / sizeof(VP)];	/* interrupt stack pointer */



/* ------------------------------------------ */
/*                kernel heap                 */
/* ------------------------------------------ */

VP kernel_heap_mem[((4096) + sizeof(VP) - 1) / sizeof(VP)];	/* kernel heap */



/* ------------------------------------------ */
/*               set time tic                 */
/* ------------------------------------------ */

const UW kernel_tic_deno = TIC_DENO;
const UW kernel_tic_div  = TIC_NUME / TIC_DENO;
const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;



/* ------------------------------------------ */
/*          create task objects               */
/* ------------------------------------------ */

/* stack area */
static VP kernel_tsk1_stk[((1024) + sizeof(VP) - 1) / sizeof(VP)];
static VP kernel_tsk2_stk[((1024) + sizeof(VP) - 1) / sizeof(VP)];

/* task control block for rom area */
const T_KERNEL_TCB_ROM kernel_tcb_rom[2] =
	{
		{(ATR)(TA_HLNG), (VP_INT)(1), (FP)(sample_task_1), (PRI)(1), (SIZE)(1024), (VP)kernel_tsk1_stk},
		{(ATR)(TA_HLNG), (VP_INT)(2), (FP)(sample_task_2), (PRI)(2), (SIZE)(1024), (VP)kernel_tsk2_stk},
	};

/* task control block for ram area */
T_KERNEL_TCB_RAM kernel_tcb_ram[2];

/* task control block table */
T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[16] =
	{
		&kernel_tcb_ram[0],
		&kernel_tcb_ram[1],
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};

/* task control block count */
const INT kernel_tcb_cnt = 16;



/* ------------------------------------------ */
/*         create semaphore objects           */
/* ------------------------------------------ */

/* semaphore control block for rom area */
const T_KERNEL_SEMCB_ROM kernel_semcb_rom[1] =
	{
		{(ATR)(TA_TFIFO), (UINT)(0), (UINT)(1)},
	};

/* semaphore control block for ram area */
T_KERNEL_SEMCB_RAM kernel_semcb_ram[1];

/* semaphore control block table */
T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[1] =
	{
		&kernel_semcb_ram[0],
	};

/* semaphore control block count */
const INT kernel_semcb_cnt = 1;



/* ------------------------------------------ */
/*        create event flag objects           */
/* ------------------------------------------ */

/* event flag control block count */
const INT kernel_flgcb_cnt = 0;



/* ------------------------------------------ */
/*        create data queue objects           */
/* ------------------------------------------ */

/* data queue control block count */
const INT kernel_dtqcb_cnt = 0;



/* ------------------------------------------ */
/*         create mail box objects            */
/* ------------------------------------------ */

/* mail box control block count */
const INT kernel_mbxcb_cnt = 0;



/* ------------------------------------------ */
/*      create message buffer objects         */
/* ------------------------------------------ */

/* mail box control block count */
const INT kernel_mbfcb_cnt = 0;



/* ------------------------------------------ */
/*   create fixed size memory-pool objects    */
/* ------------------------------------------ */

/* fixed size memory-pool control block count */
const INT kernel_mpfcb_cnt = 0;



/* ------------------------------------------ */
/*  create variable size memory-pool objects  */
/* ------------------------------------------ */

/* variable size memory-pool control block count */
const INT kernel_mplcb_cnt = 0;



/* ------------------------------------------ */
/*       create cyclic handler objects        */
/* ------------------------------------------ */

/* cyclic handler control block for rom area */
const T_KERNEL_CYCCB_ROM kernel_cyccb_rom[1] =
	{
		{(ATR)(TA_HLNG), (VP_INT)(0), (FP)(sample_cycle_handler), (RELTIM)(1000)},
	};

/* cyclic handler control block for ram area */
T_KERNEL_CYCCB_RAM kernel_cyccb_ram[1];

/* cyclic handler control block table */
T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[1] =
	{
		&kernel_cyccb_ram[0],
	};

/* cyclic handler control block count */
const INT kernel_cyccb_cnt = 1;



/* ------------------------------------------ */
/*       create alarm handler objects         */
/* ------------------------------------------ */

/* alarm handler control block count */
const INT kernel_almcb_cnt = 0;



/* ------------------------------------------ */
/*        interrupt control objects           */
/* ------------------------------------------ */

/* interrupt control */
T_KERNEL_INTCB kernel_intcb_tbl[257];		/* interrupt control block table */
const INT      kernel_intcb_cnt = 257;		/* interrupt control block count */
const INTNO    kernel_min_intno = 0;		/* minimum intrrupt number */

/* interrupt service routine control */
const INT      kernel_isrcb_cnt = 0;		/* ISR control block count */



/* ------------------------------------------ */
/*    CPU exception handler control objects   */
/* ------------------------------------------ */

/* interrupt control */
T_KERNEL_EXCCB kernel_exccb_tbl[1];		/* CPU exception handler control block table */
const INT      kernel_exccb_cnt = 1;		/* CPU exception handler control block count */
const EXCNO    kernel_min_excno = 0;		/* minimum CPU exception handler number */



/* ------------------------------------------ */
/*          initialize functions              */
/* ------------------------------------------ */

/* object initialize */
void kernel_cfg_init(void)
{
	int i;
	
	
	/* initialize task control block */
	for ( i = 0; i < 2; i++ )
	{
		kernel_tcb_ram[i].tcb_rom = &kernel_tcb_rom[i];
	}
	
	
	/* initialize semaphore control block */
	for ( i = 0; i < 1; i++ )
	{
		kernel_semcb_ram[i].semcb_rom = &kernel_semcb_rom[i];
	}
	
	
	/* initialize cyclic handler control block */
	for ( i = 0; i < 1; i++ )
	{
		kernel_cyccb_ram[i].cyccb_rom = &kernel_cyccb_rom[i];
	}

	/* initialize interrupt table */
	kernel_intcb_tbl[HOS_VN_INTTM0EQ0].exinf = (VP_INT)(0);
	kernel_intcb_tbl[HOS_VN_INTTM0EQ0].isr   = (FP)(ostim_hdr);
}

/* start up */
void kernel_cfg_start(void)
{
	kernel_ini_mem(kernel_heap_mem, sizeof(kernel_heap_mem));		/* initialize kernel heap */

	kernel_ini_tsk();		/* initialize task */
	kernel_ini_sem();		/* initialize semaphore */
	kernel_ini_cyc();		/* initialize cyclic handler */

	/* call initialize routine*/
	((FP)(sample_init))((VP_INT)(0));
	((FP)(ostim_init))((VP_INT)(0));
}


/* ------------------------------------------------------------------------ */
/*  End of file                                                             */
/* ------------------------------------------------------------------------ */
