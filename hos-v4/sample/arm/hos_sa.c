/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   サンプルプログラム                                                     */
/*   ユーザー作成関数 StrongARM用                                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 割り込みコントローラーレジスタアドレス */
#define ICIP		(*(volatile UW *)0x9005000)
#define ICMR		(*(volatile UW *)0x9005004)
#define ICLR		(*(volatile UW *)0x9005008)
#define ICFP		(*(volatile UW *)0x9005010)
#define ICPR		(*(volatile UW *)0x9005020)
#define ICCR		(*(volatile UW *)0x900500c)



/* ローカル変数 */
static UW fiq_save_imask;		/* FIQ時割り込みマスク値保存用 */



/* IRQの初期化 */
void hos_arm_ini_int(void)
{
	/* 割り込みコントローラー初期化 */
	ICMR = 0x00000000;		/* 全割り込みをマスク */
}


/* IRQ割り込み処理開始（ユーザー作成関数） */
INTNO hos_arm_sta_irq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* 割り込み番号検索 */
	status = SA_ICIP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	/* 割り込みマスク設定 */
	hospac_arm_imask |= (ARM_IMASK_IRQ | ARM_IMASK_USR_MODE);	/* IRQをマスク(FIQのみ許可) */
	
	mknl_ena_int();		/* 多重割り込み許可 */
	
	return intno;
}


/* IRQ割り込み処理終了（ユーザー作成関数） */
void  hos_arm_end_irq(void)
{
	mknl_dis_int();		/* 多重割り込み禁止 */
	
	hospac_arm_imask = ARM_IMASK_USR_MODE;	/* IRQマスクを解除 */
}


/* FIQ割り込み処理開始（ユーザー作成関数） */
INTNO hos_arm_sta_fiq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* 割り込み番号検索 */
	status = SA_ICFP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	fiq_save_imask   = hospac_arm_imask;	/* 割り込みマスク状態保存 */
	hospac_arm_imask = (ARM_IMASK_IRQ | ARM_IMASK_FIQ | ARM_IMASK_USR_MODE)
											/* 割り込みを全マスク */
	
	return intno;	/* 割り込み番号を返す */
}


/* FIQ割り込み処理終了（ユーザー作成関数） */
void  hos_arm_end_fiq(void)
{
	fiq_save_imask   = hospac_arm_imask;	/* 割り込みマスク状態復帰 */
}


/* 割り込みの許可 */
ER ena_int(INTNO intno)
{
	mknl_loc_sys();		/* システムロック */
	
	ICMR |= 0x00000001 << (intno - TMIN_INTNO);
	
	mknl_unl_sys();		/* システムロック解除 */
	
	return E_OK;
}


/* 割り込みの禁止 */
ER dis_int(INTNO intno)
{
	mknl_loc_sys();		/* システムロック */
	
	ICMR &= ~(0x00000001 << (intno - TMIN_INTNO));
	
	mknl_unl_sys();		/* システムロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
