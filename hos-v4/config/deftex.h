// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    DEF_TEX API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefTex_h__
#define __HOSV4CFG_DefTex_h__


#include "apidef.h"
#include "parpack.h"


// DEF_TEX ��
class CApiDefTex : public CApiDef
{
public:
	CApiDefTex();		// ���󥹥ȥ饯��
	~CApiDefTex();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ��ưID�ֹ�������
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�
	void  WriteCfgIni(FILE* fp);				// cfg�ե������������񤭽Ф�
};


#endif	// __HOSV4CFG_DefTex_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
