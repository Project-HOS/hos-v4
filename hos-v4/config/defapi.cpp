// ===========================================================================
//  HOS V4 ����ե�����졼����
//    API������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================

#include <stdio.h>
#include <string.h>
#include "defapi.h"


// ���󥹥ȥ饯��
CDefApi::CDefApi()
{
	m_pDefApi = NULL;
}


// �ǥ��ȥ饯��
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


// API������ɲ�
void CDefApi::AddDefine(TDefApi* pDefApi)
{
	pDefApi->pNext = m_pDefApi;
	m_pDefApi      = pDefApi;
}


// API����μ���
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
