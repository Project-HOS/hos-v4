// ===========================================================================
//  HOS V4 ����ե�����졼���� Ver 1.00
//    �ǡ����ɤ߹��ߥ��饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include <stdio.h>
#include <string.h>
#include "read.h"


#define READ_MEMALLOC_UNIT	1024	// ������ݤ�ñ��


char* CRead::m_pFileText = NULL;	// ����ե�����졼�����ե�����ǡ���
int   CRead::m_iFileSize = 0;		// ����ե�����졼�����ե����륵����


// �ե�������ɤ߹���
void CRead::ReadConfig(FILE* fpIn, FILE* fpOut)
{
	int iMemSize = READ_MEMALLOC_UNIT;
	int c;
	
	// ����ɤ߹��ߥ������
	m_pFileText = new char[iMemSize];

	// ���˥ե��������Τ��ɤ߹��ߡʼ�ȴ������
	while ( (c = getc(fpIn)) != EOF )
	{
		// stdin ��������Ϥ��θ�����ɤߤʤ���������
		if ( CRead::m_iFileSize >= iMemSize )
		{
			iMemSize += READ_MEMALLOC_UNIT;
			char* pTmp = new char[iMemSize];
			memcpy(pTmp, m_pFileText, CRead::m_iFileSize);
			delete[] m_pFileText;
			m_pFileText = pTmp;
		}

		// �ǡ�����Ǽ
		m_pFileText[m_iFileSize++] = (char)c;
	}
}


// ����
void CRead::Analize(void)
{
	bool  bLineHead = true;		// ��Ƭ�ե饰
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
