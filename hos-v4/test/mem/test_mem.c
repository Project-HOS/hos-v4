/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*  カーネルメモリ管理 の単体テストモジュール                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include <string.h>
#include "kernel.h"


#include <assert.h>
#define TEST_ASSERT(a)		assert(a)

int test_mem(void);


int main()
{
	test_mem();

	printf("OK\n");

	return 0;
}



#define TEST_MEM_SIZE		256

static UW test_mem_buf[TEST_MEM_SIZE / sizeof(UW)];
static VP test_mem_ptr[4];


/* ヒープ構造の正当性チェック */
BOOL test_mem_check_heap(void)
{
	T_KERNEL_MEM_BLK *mblk_prev = NULL;
	T_KERNEL_MEM_BLK *mblk;
	SIZE size = 0;

	mblk = kernel_mem_base;
	for ( ; ; )
	{
		size += mblk->size + MEMBLKSIZE;
		if ( mblk->flag != MEMBLK_USING &&  mblk->flag != MEMBLK_FREE )
		{
			return FALSE;	/* フラグ異常 */
		}
		
		if ( mblk->size == 0 )
		{
			break;
		}

		if ( mblk->prev != mblk_prev )
		{
			return FALSE;	/* 異常 */
		}

		mblk_prev = mblk;
		mblk      = (T_KERNEL_MEM_BLK *)((UB *)mblk + mblk->size + MEMBLKSIZE);
	}

	if ( size != kernel_mem_size )
	{
		return FALSE;	/* 異常 */
	}

	return TRUE;
}


VP test_mem_alc(SIZE size)
{
	VP ptr;

	ptr = kernel_alc_mem(size);
	if ( ptr != NULL )
	{
		memset(ptr, 0xa5, size);
	}

	return ptr;
}

void test_mem_fre(VP ptr)
{
	kernel_fre_mem(ptr);
}


int test_mem(void)
{
	int tst_loop;
	int i;

	kernel_ini_mem(test_mem_buf, TEST_MEM_SIZE);

	for ( tst_loop = 0; tst_loop < 100; tst_loop++ )
	{
		/* 1バイトから8バイトまでの取得開放テスト */
		for ( i = 1; i <= 32; i++ )
		{
			/* １個の単純取得開放 */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			
			/* ２個の取得開放(0-1) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());

			/* ２個の取得開放(1-0) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_check_heap());
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());

						
			/* ３個の取得開放(0-1-2) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());

			/* ３個の取得開放(0-2-1) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());

			/* ３個の取得開放(1-0-2) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());

			/* ３個の取得開放(1-2-0) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());

			/* ３個の取得開放(2-0-1) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_check_heap());
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());

			/* ３個の取得開放(2-1-0) */
			test_mem_ptr[0] = test_mem_alc(i);
			TEST_ASSERT(test_mem_ptr[0] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[1] = test_mem_alc(i+1);
			TEST_ASSERT(test_mem_ptr[1] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_ptr[2] = test_mem_alc(i+2);
			TEST_ASSERT(test_mem_ptr[2] != NULL);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[2]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[1]);
			TEST_ASSERT(test_mem_check_heap());
			test_mem_fre(test_mem_ptr[0]);
			TEST_ASSERT(test_mem_check_heap());
		}
	}
	
	return TRUE;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
