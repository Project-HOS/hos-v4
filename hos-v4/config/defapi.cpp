// ===========================================================================
//  HOS V4 コンフィギュレーター
//    API定義クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================

#include <stdio.h>
#include <string.h>
#include "defapi.h"


// コンストラクタ
CDefApi::CDefApi()
{
	m_pDefApi = NULL;
}


// デストラクタ
CDefApi::~CDefApi()
{
	TDefApi* pDefApi;
	TDefApi* pNext;

	pDefApi = m_pDefApi;
	while ( pDefApi!= NULL )
	{
		pNext = pDefApi->pNext;
		delete pDefApi->pParamBlock;
		delete pDefApi;
		pDefApi = pNext;
	}
}


// API定義の追加
void CDefApi::AddDefine(TDefApi* pDefApi)
{
	pDefApi->pNext = m_pDefApi;
	m_pDefApi      = pDefApi;
}


// API定義の取得
TDefApi* CDefApi::GetDefine(const char* pszApiName)
{
	TDefApi* pDefApi;

	pDefApi = m_pDefApi;
	while ( pDefApi != NULL )
	{
		if ( strcmp(pDefApi->pszApiName, pszApiName) == 0 )
		{
			break;
		}
		pDefApi = pDefApi->pNext;
	}

	return pDefApi;
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
