// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����                                               
//    HOS_TIM_TIC API �ν���                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiTimTic_h__
#define __HOSV4CFG_ApiTimTic_h__


#include "apidef.h"
#include "parpack.h"


// HOS_TIM_TIC ��
class CApiTimTic : public CApiDef
{
public:
	CApiTimTic();		// ���󥹥ȥ饯��
	~CApiTimTic();		// �ǥ��ȥ饯��

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ID ����ե�����񤭽Ф�
	void  WriteId(FILE* fp);					// cfg�ե�����������񤭽Ф�
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�

protected:
	int m_iNume;	// ������ƥ��å��μ�����ʬ��
	int m_iDeno;	// ������ƥ��å��μ�����ʬ��
};


#endif	// __HOSV4CFG_ApiTimTic_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
