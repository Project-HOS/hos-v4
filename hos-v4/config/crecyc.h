// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����                                               
//    CRE_CYC API �ν���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreCyc_h__
#define __HOSV4CFG_CreCyc_h__


#include "apidef.h"
#include "parpack.h"


// CRE_CYC ��
class CApiCreCyc : public CApiDef
{
public:
	CApiCreCyc();		// ���󥹥ȥ饯��
	~CApiCreCyc();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	void  WriteId(FILE* fp);					// ID ����ե�����񤭽Ф�
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�
	void  WriteCfgIni(FILE* fp);				// cfg�ե������������񤭽Ф�
	void  WriteCfgStart(FILE* fp);				// cfg�ե����뵯ư���񤭽Ф�
};


#endif	// __HOSV4CFG_CreCyc_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
