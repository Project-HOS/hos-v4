// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    HOS_MAX_TPRI API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtpri.h"
#include "analyze.h"



// ���󥹥ȥ饯��
CApiMaxTpri::CApiMaxTpri()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParams         = 1;

	m_iMaxPri = 16;
}


// �ǥ��ȥ饯��
CApiMaxTpri::~CApiMaxTpri()
{
}



// API�β���
int CApiMaxTpri::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	// API̾�����å�
	if ( strcmp(pszApiName, "HOS_MAX_TPRI") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxPri = atoi(pszParams);

	return CFG_ERR_OK;
}


// ʸ�����Ÿ��
int CApiMaxTpri::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�ե�����������񤭽Ф�
void  CApiMaxTpri::WriteCfgDef(FILE* fp)
{
	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*           create ready queue               */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_QUE mknl_rdq_tbl[%d];\n"
		"const INT mknl_rdq_cnt = %d;\n",
		m_iMaxPri,
		m_iMaxPri);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
