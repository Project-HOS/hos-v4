// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����                                               
//    DEF_EXC API �ν���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "defexc.h"
#include "analyze.h"


#define DEFEXC_EXCNO		0
#define DEFEXC_EXCATR		1
#define DEFEXC_EXCHDR		2


// ���󥹥ȥ饯��
CApiDefExc::CApiDefExc()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 2;		// 2�ĤΥѥ�᡼�����֥�å�
	m_iParams = 2;

	m_iMaxExcNo = 0;
	m_iMinExcNo = 0;
}

// �ǥ��ȥ饯��
CApiDefExc::~CApiDefExc()
{
}


// ��ưID�ֹ�������
int CApiDefExc::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�β���
int CApiDefExc::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "DEF_EXC") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_EXCNO") == 0 )
	{
		int iExcNo;
		if ( (iExcNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iExcNo > m_iMaxExcNo )
		{
			m_iMaxExcNo = iExcNo;
		}
		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_MIN_EXCNO") == 0 )
	{
		int iExcNo;
		if ( (iExcNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iExcNo < m_iMinExcNo )
		{
			m_iMinExcNo = iExcNo;
		}
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// cfg�ե�����������񤭽Ф�
void  CApiDefExc::WriteCfgDef(FILE* fp)
{
	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*    CPU exception handler control objects   */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// �����ߴ����ơ��֥�����
	fputs("\n/* interrupt control */\n", fp);

	if ( m_iMaxExcNo - m_iMinExcNo + 1 > 0 )
	{
		fprintf(
			fp,
			"T_KERNEL_EXCCB kernel_exccb_tbl[%d];\t\t/* CPU exception handler control block table */\n",
			m_iMaxExcNo - m_iMinExcNo + 1);
	}

	fprintf(
		fp,
		"const INT      kernel_exccb_cnt = %d;\t\t/* CPU exception handler control block count */\n"
		"const EXCNO    kernel_min_excno = %d;\t\t/* minimum CPU exception handler number */\n",
		m_iMaxExcNo - m_iMinExcNo + 1,
		m_iMinExcNo);	
}


// cfg�ե������������񤭽Ф�
void  CApiDefExc::WriteCfgIni(FILE* fp)
{
	int i;

	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �����Ƚ���
	fputs("\n\t/* initialize CPU exception handler table */\n", fp);
	
	// �����������
	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\tkernel_exccb_tbl[%s].exchdr = (FP)(%s);\n",
			m_pParamPacks[i]->GetParam(DEFEXC_EXCNO),
			m_pParamPacks[i]->GetParam(DEFEXC_EXCHDR));
	}
}



// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
