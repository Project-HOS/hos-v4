// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    ATT_ISR API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "attisr.h"
#include "analize.h"


#define ATTISR_ISRATR		0
#define ATTISR_EXINF		1
#define ATTISR_INTNO		2
#define ATTISR_ISR			3


// ���󥹥ȥ饯��
CApiAttIsr::CApiAttIsr()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 4;		// 4�ĤΥѥ�᡼�����֥�å�
	m_iParams = 1;
}

// �ǥ��ȥ饯��
CApiAttIsr::~CApiAttIsr()
{
}

// API̾����
char* CApiAttIsr::GetApiName(void)
{
	return "ATT_ISR";
}


// ��ưID�ֹ�������
int CApiAttIsr::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�ե������������񤭽Ф�
void  CApiAttIsr::WriteCfgIni(FILE* fp)
{
	int i;

	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �����Ƚ���
	fputs("\n\t/* initialize interrupt table */\n", fp);
	
	// �����������
	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\tkernel_intcb_tbl[%s].exinf = (VP_INT)(%s);\n"
			"\tkernel_intcb_tbl[%s].isr   = (FP)(%s);\n",
			m_pParamPacks[i]->GetParam(ATTISR_INTNO),
			m_pParamPacks[i]->GetParam(ATTISR_EXINF),
			m_pParamPacks[i]->GetParam(ATTISR_INTNO),
			m_pParamPacks[i]->GetParam(ATTISR_ISR));
	}
}



// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
