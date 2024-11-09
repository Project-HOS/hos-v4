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
static VP test_mem_ptr[10];



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


/* メモリ割り当て */
VP test_mem_alc(SIZE size)
{
	VP  ptr;
	int x;
	int i;

	ptr = kernel_alc_mem(size);
	if ( ptr != NULL )
	{
		/* 取得した範囲のメモリに書き込み */
		x = (int)ptr;
		*(UB *)ptr = (UB)size;
		for ( i = 1; i < (int)size; i++ )
		{
			*((UB *)ptr + i) = (UB)x++;
		}
	}

	return ptr;
}


/* メモリ開放 */
void test_mem_fre(VP ptr)
{
	SIZE size;
	int  x;
	int  i;

	if ( ptr != NULL )
	{
		/* 取得した範囲のメモリが破壊されていないかチェック */
		x    = (int)ptr;
		size = *(UB *)ptr;
		for ( i = 1; i < (int)size; i++ )
		{
			TEST_ASSERT(*((UB *)ptr + i) == (UB)x);
			x++;
		}
	}

	kernel_fre_mem(ptr);
}



/* 基本テストセット */
void test_mem_sub(void)
{
	int i;

	/* 1バイトから32バイトまでサイズを振ってみるテスト */
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


int test_mem(void)
{
	kernel_ini_mem(test_mem_buf, TEST_MEM_SIZE);

	/* 普通にテスト */
	test_mem_sub();

	/* フラグメントを起こしてからテスト */
	test_mem_ptr[4] = test_mem_alc(64);
	TEST_ASSERT(test_mem_ptr[0] != NULL);
	test_mem_ptr[5] = test_mem_alc(15);
	TEST_ASSERT(test_mem_ptr[0] != NULL);
	test_mem_fre(test_mem_ptr[4]);
	test_mem_sub();
	test_mem_fre(test_mem_ptr[5]);
	TEST_ASSERT(test_mem_check_heap());
	
	
	
	return TRUE;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
