// ---------------------------------------------------------------------------
//  Hyper Operating System V4  ����ե�����졼����                           
//    CRE_MPF API �ν���                                                      
//                                                                            
//                                    Copyright (C) 1998-2006 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreMpl_h__
#define __HOSV4CFG_CreMpl_h__


#include "apidef.h"
#include "parpack.h"


// CRE_MPL ��
class CApiCreMpl : public CApiDef
{
public:
	CApiCreMpl();		// ���󥹥ȥ饯��
	~CApiCreMpl();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	void  WriteId(FILE* fp);					// ID ����ե�����񤭽Ф�
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�
	void  WriteCfgIni(FILE* fp);				// cfg�ե������������񤭽Ф�
	void  WriteCfgStart(FILE* fp);				// cfg�ե����뵯ư���񤭽Ф�
};


#endif	// __HOSV4CFG_CreMpl_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2006 by Project HOS                                    
// ---------------------------------------------------------------------------
