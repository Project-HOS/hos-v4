// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    INCLUDE API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiInclude_h__
#define __HOSV4CFG_ApiInclude_h__


#include "apidef.h"
#include "parpack.h"


// INCLUDE ��
class CApiInclude : public CApiDef
{
public:
	CApiInclude();		// ���󥹥ȥ饯��
	~CApiInclude();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ��ưID�ֹ�������
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�
};


#endif	// __HOSV4CFG_ApiInclude_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
