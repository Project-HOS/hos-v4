// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    CRE_MBX API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crembx.h"
#include "analize.h"


#define CREMBX_MBXID		0
#define CREMBX_MBXATR		1
#define CREMBX_MAXPRI		2
#define CREMBX_MPRIHD		3



// ���󥹥ȥ饯��
CApiCreMbx::CApiCreMbx()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 3;		// 3�ѥ�᡼�����Υ֥��å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreMbx::~CApiCreMbx()
{
}



// API�β���
int CApiCreMbx::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_MBX") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_MBXID") == 0 )
	{
		int iId;
		if ( (iId = atoi(pszParams)) <= 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iId > m_iMaxId )
		{
			m_iMaxId = iId;
		}
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// ID ����ե�����񤭽Ф�
void CApiCreMbx::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMBX_MBXID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* mail box ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMBX_MBXID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREMBX_MBXID),
				m_iId[i]);
		}
	}
}


// cfg�ե�����������񤭽Ф�
void  CApiCreMbx::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*         create mail box objects            */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block for rom area */\n"
			"const T_KERNEL_MBXCB_ROM kernel_mbxcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ�����֥��å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s)},",
				m_pParamPacks[i]->GetParam(CREMBX_MBXATR));
		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ�����֥��å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block for ram area */\n"
			"T_KERNEL_MBXCB_RAM kernel_mbxcb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ�����֥��å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block table */\n"
			"T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[%d] =\n"
			"\t{\n",
			m_iMaxId);

		for ( i = 0; i < m_iMaxId; i++ )
		{
			// ID����
			for ( j = 0; j < m_iObjs; j++ )
			{
				if ( m_iId[j] == i + 1 )
				{
					break;
				}
			}
			if ( j < m_iObjs )
			{
				// ���֥������Ȥ�¸�ߤ������
				fprintf(fp, "\t\t&kernel_mbxcb_ram[%d],\n", j);
			}
			else
			{
				// ���֥������Ȥ�̵�����
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// �Ŀ��������
	fprintf(
		fp,
		"\n/* mail box control block count */\n"
		"const INT kernel_mbxcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreMbx::WriteCfgIni(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �����������
	fprintf(
		fp,
		"\t\n\t\n"
		"\t/* initialize mail box control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_mbxcb_ram[i].mbxcbrom = &kernel_mbxcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreMbx::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_mbx();\t\t/* initialize mail box */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------