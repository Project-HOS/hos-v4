// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    ATT_INI API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiAttIni_h__
#define __HOSV4CFG_ApiAttIni_h__


#include "apidef.h"
#include "parpack.h"


// ATT_INI ��
class CApiAttIni : public CApiDef
{
public:
	CApiAttIni();		// ���󥹥ȥ饯��
	~CApiAttIni();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ��ưID�ֹ�������
	void  WriteCfgStart(FILE* fp);				// cfg�ե�����������񤭽Ф�
};


#endif	// __HOSV4CFG_ApiAttIni_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
