// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    CRE_FLG API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "creflg.h"
#include "analize.h"



#define CREFLG_FLGID		0
#define CREFLG_FLGATR		1
#define CREFLG_IFLGPTN		2



// ���󥹥ȥ饯��
CApiCreFlg::CApiCreFlg()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 2;		// 2�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreFlg::~CApiCreFlg()
{
}


// API�β���
int CApiCreFlg::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_FLG") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_FLGID") == 0 )
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
void CApiCreFlg::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREFLG_FLGID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* event flag ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREFLG_FLGID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREFLG_FLGID),
				m_iId[i]);
		}
	}
}


// cfg�ե�����������񤭽Ф�
void  CApiCreFlg::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*        create event flag objects           */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* event flag control block for rom area */\n"
			"const T_KERNEL_FLGCB_ROM kernel_flgcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ���֥�å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (FLGPTN)(%s)},\n",
				m_pParamPacks[i]->GetParam(CREFLG_FLGATR),
				m_pParamPacks[i]->GetParam(CREFLG_IFLGPTN));
		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ���֥�å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* event flag control block for ram area */\n"
			"T_KERNEL_FLGCB_RAM kernel_flgcb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ���֥�å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* event flag control block table */\n"
			"T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_flgcb_ram[%d],\n", j);
			}
			else
			{
				// ���֥������Ȥ�̵�����
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// �ơ��֥륵�����������
	fprintf(
		fp,
		"\n/* event flag control block count */\n"
		"const INT kernel_flgcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreFlg::WriteCfgIni(FILE* fp)
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
		"\t/* initialize event flag control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_flgcb_ram[i].flgcbrom = &kernel_flgcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreFlg::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_flg();\t\t/* initialize event flag */\n", fp);
}


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
