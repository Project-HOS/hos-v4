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

	m_iIntStackSize = 128;
	m_iMaxIntNo = 0;
	m_iMinIntNo = 0;
	m_iMaxIsrId = 0;
}

// �ǥ��ȥ饯��
CApiAttIsr::~CApiAttIsr()
{
}


// ��ưID�ֹ�������
int CApiAttIsr::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�β���
int CApiAttIsr::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "ATT_ISR") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_INTNO") == 0 )
	{
		int iIntNo;
		if ( (iIntNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iIntNo > m_iMaxIntNo )
		{
			m_iMaxIntNo = iIntNo;
		}
		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_MIN_INTNO") == 0 )
	{
		int iIntNo;
		if ( (iIntNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iIntNo < m_iMinIntNo )
		{
			m_iMinIntNo = iIntNo;
		}
		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_MAX_ISRID") == 0 )
	{
		int iId;
		if ( (iId = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iId > m_iMaxIsrId )
		{
			m_iMaxIsrId = iId;
		}
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// cfg�ե�����������񤭽Ф�
void  CApiAttIsr::WriteCfgDef(FILE* fp)
{
	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*        interrupt control objects           */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// �������ѥ����å�����
	fprintf(
		fp,
		"\n"
		"/* interrupt stack */\n"
		"VP       kernel_int_stk[(%d + sizeof(VP) - 1) / sizeof(VP)];\n"
		"const VP kernel_int_sp = &kernel_int_stk[(%d + sizeof(VP) - 1) / sizeof(VP)];\n",
		m_iIntStackSize,
		m_iIntStackSize);

	// �����ߴ����ơ��֥�����
	fprintf(
		fp,
		"\n"
		"/* interrupt control */\n"
		"T_KERNEL_INTCB kernel_intcb_tbl[%d];\t\t/* interrupt control block table */\n"
		"const INT      kernel_intcb_cnt = %d;\t\t/* interrupt control block count */\n"
		"const INTNO    kernel_min_intno = %d;\t\t/* minimum intrrupt number */\n",
		m_iMaxIntNo - m_iMinIntNo + 1,
		m_iMaxIntNo - m_iMinIntNo + 1,
		m_iMinIntNo);
	
	// ISR����ȥ���ơ��֥�����
	if ( m_iMaxIsrId > 0 )
	{
		fprintf(
			fp,
			"\n"
			"/* interrupt service routine control */\n"
			"T_KERNEL_ISRCB kernel_isrcb_tbl[%d];\t\t/* ISR control block table */\n"
			"const INT      kernel_isrcb_cnt = %d;\t\t/* ISR control block count */\n",
			m_iMaxIsrId,
			m_iMaxIsrId);
	}
	else
	{
		fprintf(
			fp,
			"\n"
			"/* interrupt service routine control */\n"
			"const INT      kernel_isrcb_cnt = %d;\t\t/* ISR control block count */\n",
			m_iMaxIsrId,
			m_iMaxIsrId);
	}
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



// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
