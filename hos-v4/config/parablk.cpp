// ===========================================================================
//  HOS V4 コンフィギュレーター
//    パラメーターブロック管理クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include <stdio.h>
#include "parablk.h"
#include "paranull.h"


// コンストラクタ
CParamBlock::CParamBlock(int iMaxParam, int iMinParam)
{
	int i;

	/* 最大最小値保存 */
	m_iMaxParam = iMaxParam;
	m_iMinParam = iMinParam;

	/* パラメーターリストメモリ確保 */
	m_ppPramList = new CParamType*[m_iMinParam];
	
	/* パラメーターリスト初期化 */
	for ( i = 0; i < m_iMinParam; i++ )
	{
		m_ppPramList[i] = new CParamNull();
	}
}


// デストラクタ
CParamBlock::~CParamBlock()
{
	int i;

	/* パラメーターリストの破棄 */
	for ( i = 0; i < m_iMinParam; i++ )
	{
		delete m_ppPramList[i];
	}
	delete[] m_ppPramList;
}


// 型タイプ取得
int CParamBlock::GetParamType()
{
	return PARAMTYPE_BLOCK;
}


// パラメーターの設定
void CParamBlock::SetParam(int iIndex, CParamType* pParamType)
{
	// 範囲チェック
	if ( iIndex <= 0 || iIndex >= m_iMinParam )
	{
		return;
	}

	// パラメーターの設定
	delete m_ppPramList[iIndex];
	m_ppPramList[iIndex] = pParamType;
}


// パラメーターの取得
CParamType* CParamBlock::GetParam(int iIndex)
{
	// 範囲チェック
	if ( iIndex <= 0 || iIndex >= m_iMinParam )
	{
		return NULL;
	}

	return m_ppPramList[iIndex];
}


// パラメーター文字列の設定
int CParamBlock::SetParamString(const char* pszParam)
{
	int iParamNum;
	int iBase;
	int i;

	iBase = 0;
	for ( iParamNum = 0; iParamNum < m_iMaxParam; iParamNum++ )
	{
	}

	return PARAMTYPE_ERR_OK;
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
