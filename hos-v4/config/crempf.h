// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    CRE_MPF API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreMpf_h__
#define __HOSV4CFG_CreMpf_h__


#include "apidef.h"
#include "parpack.h"


// CRE_MPF ��
class CApiCreMpf : public CApiDef
{
public:
	CApiCreMpf();		// ���󥹥ȥ饯��
	~CApiCreMpf();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	void  WriteId(FILE* fp);					// ID ����ե�����񤭽Ф�
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�
	void  WriteCfgIni(FILE* fp);				// cfg�ե������������񤭽Ф�
	void  WriteCfgStart(FILE* fp);				// cfg�ե����뵯ư���񤭽Ф�
};


#endif	// __HOSV4CFG_CreMpf_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
