// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    DEF_TEX API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "deftex.h"
#include "analyze.h"


#define DEFTEX_TSKID		0
#define DEFTEX_TEXATR		1
#define DEFTEX_TEXRTN		2



// ���󥹥ȥ饯��
CApiDefTex::CApiDefTex()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 2;		// 2�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiDefTex::~CApiDefTex()
{
}


// API�β���
int CApiDefTex::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "DEF_TEX") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// ��ưID�ֹ�������
int CApiDefTex::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�ե�����������񤭽Ф�
void  CApiDefTex::WriteCfgDef(FILE* fp)
{
	int  i;

	if ( m_iObjs <= 0 )
	{
		return;
	}

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          task exception objects            */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	fprintf(
		fp,
		"\n/* task exception control block */\n"
		"const T_KERNEL_TEXCB_RAM kernel_texcb_ram[%d] =\n"
		"\t{\n",
		m_iObjs);

	// ����ȥ���֥�å�(ROM��)����
	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\t\t{0, (FP)(%s)},\n",
			m_pParamPacks[i]->GetParam(DEFTEX_TEXRTN));
	}
	fprintf(fp, "\t};\n");
}


// cfg�ե������������񤭽Ф�
void  CApiDefTex::WriteCfgIni(FILE* fp)
{
	int i;

	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �����������
	fputs(
		"\t\n\t\n"
		"\t/* initialize task exception handler */\n",
		fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\tkernel_tcb_ram_tbl[(%s) - TMIN_TSKID]->texcb = &kernel_texcb_rom[%d];\n",
			m_pParamPacks[i]->GetParam(DEFTEX_TSKID),
			i);
	}
}



// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
