// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    ATT_ISR API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "knlheap.h"
#include "analize.h"



// ���󥹥ȥ饯��
CApiKernelHeap::CApiKernelHeap()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParams = 1;
}


// �ǥ��ȥ饯��
CApiKernelHeap::~CApiKernelHeap()
{
}


// ��ưID�ֹ�������
int CApiKernelHeap::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�β���
int CApiKernelHeap::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_KERNEL_HEAP") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// cfg�ե�����������񤭽Ф�
void  CApiKernelHeap::WriteCfgDef(FILE* fp)
{
	if ( m_iObjs <= 0 )
	{
		return;
	}

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*                kernel heap                 */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// �ҡ����ΰ�����
	fprintf(
		fp,
		"\n"
		"VP kernel_heap_mem[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* kernel heap */\n",
		m_pParamPacks[0]->GetParam(0));
}


// cfg�ե����뵯ư���񤭽Ф�
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
