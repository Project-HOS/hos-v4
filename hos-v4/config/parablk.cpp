// ===========================================================================
//  HOS V4 ����ե�����졼����
//    �ѥ�᡼�����֥�å��������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include <stdio.h>
#include "parablk.h"
#include "paranull.h"


// ���󥹥ȥ饯��
CParamBlock::CParamBlock(int iMaxParam, int iMinParam)
{
	int i;

	/* ����Ǿ�����¸ */
	m_iMaxParam = iMaxParam;
	m_iMinParam = iMinParam;

	/* �ѥ�᡼�����ꥹ�ȥ������ */
	m_ppPramList = new CParamType*[m_iMinParam];
	
	/* �ѥ�᡼�����ꥹ�Ƚ���� */
	for ( i = 0; i < m_iMinParam; i++ )
	{
		m_ppPramList[i] = new CParamNull();
	}
}


// �ǥ��ȥ饯��
CParamBlock::~CParamBlock()
{
	int i;

	/* �ѥ�᡼�����ꥹ�Ȥ��˴� */
	for ( i = 0; i < m_iMinParam; i++ )
	{
		delete m_ppPramList[i];
	}
	delete[] m_ppPramList;
}


// �������׼���
int CParamBlock::GetParamType()
{
	return PARAMTYPE_BLOCK;
}


// �ѥ�᡼����������
void CParamBlock::SetParam(int iIndex, CParamType* pParamType)
{
	// �ϰϥ����å�
	if ( iIndex <= 0 || iIndex >= m_iMinParam )
	{
		return;
	}

	// �ѥ�᡼����������
	delete m_ppPramList[iIndex];
	m_ppPramList[iIndex] = pParamType;
}


// �ѥ�᡼�����μ���
CParamType* CParamBlock::GetParam(int iIndex)
{
	// �ϰϥ����å�
	if ( iIndex <= 0 || iIndex >= m_iMinParam )
	{
		return NULL;
	}

	return m_ppPramList[iIndex];
}


// �ѥ�᡼����ʸ���������
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
