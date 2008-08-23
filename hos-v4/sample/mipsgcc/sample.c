/*******************************************************************************
 * Hyper Operating System V4  ����ץ�ץ����
 *
 *  �ƥ������ε�ư����ȥ�����̾�򥷥ꥢ�륳�󥽡����ɽ������ץ����
 *      ������̾    ͥ����  ��ư���
 *      Task1       1       Task2�����sig_sem()�ˤ�굯ư
 *      Task2       2       1[s]�����μ��������ޤˤ�굯ư
 *
 *                                      Copyright (C) 1998-2007 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/

#include <semb1200a/semb1200a.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"
#include "irq_sample.h"
#include <math.h>

/**
 *  main�ؿ�
 */
int
main(void)
{
	/* HOS-V4 �γ��� */
	sta_hos();
	return 0;
}

/**
 *  ������ؿ�
 *  �������ε�ư��Ԥ�
 */
void
sample_init (VP_INT exinf)
{
	act_tsk (TSKID_SAMPLE_1);
	act_tsk (TSKID_SAMPLE_2);
	act_tsk (TSKID_SAMPLE_3);

	/* ���������ޤε�ư */
	sta_cyc (CYCID_SAMPLE_1);
}

/**
 *  ����ץ륿����1
 *  - ������2�����ޥե���������ޤ��Ԥ�
 *  - ���߻���ȥ�����̾��ɽ��
 */
void
sample_task_1 (VP_INT exinf)
{
	for (;;) {
		wai_sem (SEMID_SAMPLE_1);
		sample_print (1);
	}
}

/**
 *  ����ץ륿����2
 *  - 1[s]�δ�sleep����
 *  - ���ޥե�����
 *  - ���߻���ȥ�����̾��ɽ��
 */

double	b;

void
sample_task_2 (VP_INT exinf)
{
	static double	a = 0.0;

	for (;;){
		slp_tsk ();
		sig_sem (SEMID_SAMPLE_1);
		a += 0.1f;
		b = sin( a / M_PI );
		sample_print (2);
	}
}

void
sample_task_3 (VP_INT exinf)
{
	volatile double	a = 0.0, c;

	for (;;){
		a += 0.1f;
		c = cos( a / M_PI );
		uart1_putc( '.' );
		dly_tsk(100);
	}
}

/**
 *  ���߻���ȥ�����no��ɽ������
 */
void
sample_print (int no)
{
	SYSTIM st;

	get_tim (&st);

	uart1_putc ('0'+ (st.ltime / 10000) % 10);
	uart1_putc ('0'+ (st.ltime / 1000) % 10);
	uart1_putc ('0'+ (st.ltime / 100) % 10);
	uart1_putc ('0'+ (st.ltime / 10) % 10);
	uart1_putc ('0'+ (st.ltime / 1) % 10);
	uart1_puts (":Task ");
	uart1_putc ('0'+no);

	if( no == 2 ) {
		uart1_putc( ' ' );
		uart1_outval( flag_tc0 );
		uart1_putc( ' ' );
		uart1_outval( (int)(b * 10000.0) );
		uart1_putc( ' ' );
	}
	uart1_puts ("\n\r");
}

void
sample_cycle_handler (VP_INT exinf)
{
	iwup_tsk (TSKID_SAMPLE_2);
}
