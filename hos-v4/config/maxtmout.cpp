// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    HOS_MAX_TIMOUT API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtmout.h"
#include "analize.h"



// ���󥹥ȥ饯��
CApiMaxTimout::CApiMaxTimout()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParams         = 1;

	m_iMaxTimout = 16;
}


// �ǥ��ȥ饯��
CApiMaxTimout::~CApiMaxTimout()
{
}



// API�β���
int CApiMaxTimout::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	// API̾�����å�
	if ( strcmp(pszApiName, "HOS_MAX_TIMOUT") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxTimout = atoi(pszParams);

	return CFG_ERR_OK;
}


// ʸ�����Ÿ��
int CApiMaxTimout::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�ե�����������񤭽Ф�
void  CApiMaxTimout::WriteCfgDef(FILE* fp)
{
	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          create time-out queue             */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_TIMOUT mknl_timout[%d];\n"
		"const INT     mknl_timout_size = %d;\n",
		m_iMaxTimout,
		m_iMaxTimout);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
