// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    DEF_EXC API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefExc_h__
#define __HOSV4CFG_DefExc_h__


#include "apidef.h"
#include "parpack.h"


// DEF_EXC ��
class CApiDefExc : public CApiDef
{
public:
	CApiDefExc();		// ���󥹥ȥ饯��
	~CApiDefExc();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);	// cfg�ե�����������񤭽Ф�
	void  WriteCfgIni(FILE* fp);	// cfg�ե������������񤭽Ф�

protected:
	int m_iMaxExcNo;
	int m_iMinExcNo;
};


#endif	// __HOSV4CFG_DefExc_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
