// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    ATT_ISR API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "knlheap.h"
#include "analize.h"



// コンストラクタ
CApiKernelHeap::CApiKernelHeap()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParams = 1;
}


// デストラクタ
CApiKernelHeap::~CApiKernelHeap()
{
}


// 自動ID番号割り当て
int CApiKernelHeap::AutoId(void)
{
	return CFG_ERR_OK;
}


// APIの解析
int CApiKernelHeap::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_KERNEL_HEAP") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// cfgファイル定義部書き出し
void  CApiKernelHeap::WriteCfgDef(FILE* fp)
{
	if ( m_iObjs <= 0 )
	{
		return;
	}

	// コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*                kernel heap                 */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// ヒープ領域生成
	fprintf(
		fp,
		"\n"
		"VP kernel_heap_mem[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* kernel heap */\n",
		m_pParamPacks[0]->GetParam(0));
}


// cfgファイル起動部書き出し
void  CApiKernelHeap::WriteCfgStart(FILE* fp)
{
	if ( m_iObjs <= 0 )
	{
		return;
	}

	fputs("\tkernel_ini_mem(kernel_heap_mem, sizeof(kernel_heap_mem));\t\t/* initialize kernel heap */\n\n", fp);
}



// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
