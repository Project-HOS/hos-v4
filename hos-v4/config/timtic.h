// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    HOS_TIM_TIC API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiTimTic_h__
#define __HOSV4CFG_ApiTimTic_h__


#include "apidef.h"
#include "parpack.h"


// CRE_TSK ��
class CApiTimTic : public CApiDef
{
public:
	CApiTimTic();		// ���󥹥ȥ饯��
	~CApiTimTic();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ID ����ե�����񤭽Ф�
	void  WriteId(FILE* fp);					// cfg�ե�����������񤭽Ф�
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�

protected:
	int m_iNume;	// ������ƥ��å��μ�����ʬ��
	int m_iDeno;	// ������ƥ��å��μ�����ʬ��
};


#endif	// __HOSV4CFG_ApiTimTic_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------