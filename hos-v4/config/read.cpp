// ===========================================================================
//  HOS V4 コンフィギュレーター Ver 1.00
//    データ読み込みクラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include <stdio.h>
#include <string.h>
#include "read.h"


#define READ_MEMALLOC_UNIT	1024	// メモリ確保の単位


char* CRead::m_pFileText = NULL;	// コンフィギュレーションファイルデータ
int   CRead::m_iFileSize = 0;		// コンフィギュレーションファイルサイズ


// ファイルの読み込み
void CRead::ReadConfig(FILE* fpIn, FILE* fpOut)
{
	int iMemSize = READ_MEMALLOC_UNIT;
	int c;
	
	// 初期読み込みメモリ確保
	m_pFileText = new char[iMemSize];

	// 初めにファイル全体を読み込み（手抜き！）
	while ( (c = getc(fpIn)) != EOF )
	{
		// stdin からの入力を考慮して読みながらメモリ確保
		if ( CRead::m_iFileSize >= iMemSize )
		{
			iMemSize += READ_MEMALLOC_UNIT;
			char* pTmp = new char[iMemSize];
			memcpy(pTmp, m_pFileText, CRead::m_iFileSize);
			delete[] m_pFileText;
			m_pFileText = pTmp;
		}

		// データ格納
		m_pFileText[m_iFileSize++] = (char)c;
	}
}


// 解析
void CRead::Analize(void)
{
	bool  bLineHead = true;		// 行頭フラグ
	char* pPtr;

	pPtr = m_pFileText;

	while ( *pPtr != '\0' )
	{
		pPtr++;
	}
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
