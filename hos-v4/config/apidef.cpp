// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    API������饹
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include "defercd.h"
#include "apidef.h"
#include "analize.h"



// ���󥹥ȥ饯��
CApiDef::CApiDef()
{
	int i;

	m_iMaxId = 0;
	m_iObjs  = 0;
	for ( i = 0; i < API_MAX_OBJS; i++ )
	{
		m_pParamPacks[i] = NULL;
		m_iId[i]         = 0;
	}
}


// �ǥ��ȥ饯��
CApiDef::~CApiDef()
{
	int i;

	for ( i = 0; i < API_MAX_OBJS; i++ )
	{
		delete m_pParamPacks[i];
	}
}


// �ѥ�᡼�����ɲá�Ķ��ȴ����
int CApiDef::AddParams(const char* pszParams)
{
	char szParamBlock[API_MAX_PARAM];
	char szParam[API_MAX_PARAM];
	int  iErr;
	int  iIndex = 0;
	int  i, j;

	// �ѥ�᡼����Ǽ�ѥ��֥�����������
	m_pParamPacks[m_iObjs] = new CParamPack();

	for ( i = 0; i < m_iParams; i++ )
	{
		if ( m_iParamSyntax[i] == 0 )
		{
			// ñ�ȥѥ�᡼�����ڤ�Ф�
			iErr = CAnalize::GetParameter(szParam, pszParams);
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}

			// �ѥ�᡼�����ɲ�
			CAnalize::SpaceCut(szParam);
			m_pParamPacks[m_iObjs]->SetParam(iIndex++, szParam);
		}
		else
		{
			// �����ɤ����Ф�
			while ( *pszParams == ' ' )
			{
				pszParams++;
			}

			// �֥�å����ϥ����å�
			if ( *pszParams++ != '{' )
			{
				iErr = CFG_ERR_SYNTAX;
				break;
			}
			
			// �֥�å��ڤ�Ф�
			iErr = CAnalize::SearchChar(szParamBlock, pszParams, '}');
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}

			// �֥�å����ɤ߽Ф�
			const char* pszParamBlock = szParamBlock;
			for ( j = 0; j < m_iParamSyntax[i]; j++ )
			{
				// ñ�ȥѥ�᡼�����ڤ�Ф�
				iErr = CAnalize::GetParameter(szParam, pszParamBlock);
				if ( iErr != CFG_ERR_OK )
				{
					break;
				}

				// �ѥ�᡼�����ɲ�
				CAnalize::SpaceCut(szParam);
				m_pParamPacks[m_iObjs]->SetParam(iIndex++, szParam);
			}
			if ( j != m_iParamSyntax[i] )
			{
				iErr = CFG_ERR_SYNTAX;
				break;
			}
		}
	}

	if ( iErr == CFG_ERR_OK )
	{
		m_iObjs++;
	}

	return iErr;
}


// ��ưID�ֹ�������
int CApiDef::AutoId(void)
{
	bool blUsedId[255];
	int iId;
	int i;

	// �ѿ������
	for ( i = 0; i < 255; i++ )
	{
		blUsedId[i] = false;
	}

	// �����ͻ����ID�򥵡���
	for ( i = 0; i < m_iObjs; i++ )
	{
		iId = atoi(m_pParamPacks[i]->GetParam(0));
		if ( iId > 0 )
		{
			if ( m_iId[i] != 0 )
			{
				return CFG_ERR_ID_CONFLICT;		// ID����
			}
			m_iId[i] = iId;
			blUsedId[iId - 1] = true;
			if ( iId > m_iMaxId )
			{
				m_iMaxId = iId;
			}
		}
	}

	// ID ��ư����
	iId = 1;
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( m_iId[i] == 0 )
		{
			// ���ѺѤ�ID�Υ����å�
			while ( blUsedId[iId - 1] )
			{
				iId++;
			}
			m_iId[i] = iId++;
		}
	}
	iId--;

	if ( iId > m_iMaxId )
	{
		m_iMaxId = iId;
	}

	return 0;
}


// ID ����ե�����񤭽Ф�
void CApiDef::WriteId(FILE* fpId)
{
}


// cfg�ե�����������񤭽Ф�
void CApiDef::WriteCfgDef(FILE* fpCfg)
{
}

// cfg�ե������������񤭽Ф�
void CApiDef::WriteCfgIni(FILE* fpCfg)
{
}

// cfg�ե����뵯ư���񤭽Ф�
void CApiDef::WriteCfgStart(FILE* fpCfg)
{
}


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
