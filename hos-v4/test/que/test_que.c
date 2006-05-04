/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  μカーネル キュー の単体テストモジュール                                */
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


/* キューが全部外れていることをチェック */
BOOL check_que_empty(void)
{
	int i;

	if ( test_que.head != NULL )
	{
		return FALSE;		/* 異常 */
	}

	for ( i = 0; i < TEST_QUE_NUM; i++ )
	{
		if ( test_tcb[0].que != NULL )
		{
			return FALSE;	/* 異常 */
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
	/*           FIFO順              */
	/* ----------------------------- */

	/* 1個の付け外し */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());
	

	/* 2個の付け外し(先頭外し) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());

	/* 2個の付け外し(末尾外し) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TFIFO);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());


	/* 3個の付け外し(先→中→末の順で取り外し) */
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

	/* 3個の付け外し(先→末→中の順で取り外し) */
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

	/* 3個の付け外し(中→先→末の順で取り外し) */
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

	/* 3個の付け外し(中→末→先の順で取り外し) */
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

	/* 3個の付け外し(末→先→中の順で取り外し) */
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

	/* 3個の付け外し(末→中→先の順で取り外し) */
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
	/*          優先度順             */
	/* ----------------------------- */

	/* 1個の付け外し */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());


	/* 2個の付け外し(優先度：1→2) */
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(check_que_empty());
	
	/* 2個の付け外し(優先度：2→1) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[0], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[0]);
	mknl_rmv_que(&test_tcb[0]);
	TEST_ASSERT(check_que_empty());

	/* 2個の付け外し(優先度：2→2 (FIFO順になるはず)) */
	mknl_add_que(&test_que, &test_tcb[1], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_add_que(&test_que, &test_tcb[4], TA_TPRI);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[1]);
	mknl_rmv_que(&test_tcb[1]);
	TEST_ASSERT(mknl_ref_qhd(&test_que) == &test_tcb[4]);
	mknl_rmv_que(&test_tcb[4]);
	TEST_ASSERT(check_que_empty());


	/* 3個の付け外し(優先度：1→2→3) */
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

	/* 3個の付け外し(優先度：1→3→2) */
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

	/* 3個の付け外し(優先度：2→1→3) */
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
	
	/* 3個の付け外し(優先度：2→3→1) */
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

	/* 3個の付け外し(優先度：3→1→2) */
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

	/* 3個の付け外し(優先度：3→2→1) */
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


	/* 3個の付け外し(同優先混ぜ：先頭) */
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

	/* 3個の付け外し(同優先混ぜ：中) */
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

	/* 3個の付け外し(同優先混ぜ：末尾) */
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

	/* 3個の付け外し(ＡＬＬ：おまけ) */
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



