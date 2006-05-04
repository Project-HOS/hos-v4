/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*  �̥����ͥ� ���塼 ��ñ�Υƥ��ȥ⥸�塼��                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"


#include <assert.h>
#define TEST_ASSERT(a)		assert(a)

int que_test(void);


int main()
{
	que_test();

	printf("OK\n");

	return 0;
}





#define TEST_QUE_NUM	4

static T_MKNL_TCB test_tcb[TEST_QUE_NUM];
static T_MKNL_QUE test_que; 


/* ���塼����������Ƥ��뤳�Ȥ�����å� */
BOOL check_que_empty(void)
{
	int i;

	if ( test_que.head != NULL )
	{
		return FALSE;		/* �۾� */
	}

	for ( i = 0; i < TEST_QUE_NUM; i++ )
	{
		if ( test_tcb[0].que != NULL )
		{
			return FALSE;	/* �۾� */
		}
	}

	return TRUE;
}


int que_test(void)
{
	/* Initialize */
	mknl_ini_que(&test_que);
	test_tcb[0].que    = NULL;
	test_tcb[0].tskpri = 1;
	test_tcb[1].que    = NULL;
	test_tcb[1].tskpri = 2;
	test_tcb[2].que    = NULL;
	test_tcb[2].tskpri = 3;
	test_tcb[3].que    = NULL;
	test_tcb[3].tskpri = 1;
	test_tcb[4].que    = NULL;
	test_tcb[4].tskpri = 2;
	test_tcb[5].que    = NULL;
	test_tcb[5].tskpri = 3;


	/* ----------------------------- */
	/*           FIFO��              */
	/* ----------------------------- */

	/* 1�Ĥ��դ����� */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());
	

	/* 2�Ĥ��դ�����(��Ƭ����) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());

	/* 2�Ĥ��դ�����(��������) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());


	/* 3�Ĥ��դ�����(�袪�梪���ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(�袪������ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(�梪�袪���ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(�梪������ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(�����袪��ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(�����梪��ν�Ǽ�곰��) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());

	
	/* ----------------------------- */
	/*          ͥ���ٽ�             */
	/* ----------------------------- */

	/* 1�Ĥ��դ����� */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());


	/* 2�Ĥ��դ�����(ͥ���١�1��2) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());
	
	/* 2�Ĥ��դ�����(ͥ���١�2��1) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());

	/* 2�Ĥ��դ�����(ͥ���١�2��2 (FIFO��ˤʤ�Ϥ�)) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[4], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[4]);
	mknl_rmv_que(&test_tcb[4]);
	TEST_ASSERT(check_que_empty());


	/* 3�Ĥ��դ�����(ͥ���١�1��2��3) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(ͥ���١�1��3��2) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(ͥ���١�2��1��3) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());
	
	/* 3�Ĥ��դ�����(ͥ���١�2��3��1) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(ͥ���١�3��1��2) */
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(ͥ���١�3��2��1) */
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());


	/* 3�Ĥ��դ�����(Ʊͥ�躮������Ƭ) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[3], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[3]);
	mknl_rmv_que(&test_tcb[3]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(Ʊͥ�躮������) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[4], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[4]);
	mknl_rmv_que(&test_tcb[4]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(Ʊͥ�躮��������) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[5], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[5]);
	mknl_rmv_que(&test_tcb[5]);
	TEST_ASSERT(check_que_empty());

	/* 3�Ĥ��դ�����(���̡̣����ޤ�) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[2], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[3], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[4], TA_TPRI);
	mknl_add_que(&test_que, &test_tcb[5], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[3]);
	mknl_rmv_que(&test_tcb[3]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[4]);
	mknl_rmv_que(&test_tcb[4]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[2]);
	mknl_rmv_que(&test_tcb[2]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[5]);
	mknl_rmv_que(&test_tcb[5]);
	TEST_ASSERT(check_que_empty());

	
	return TRUE;
}



