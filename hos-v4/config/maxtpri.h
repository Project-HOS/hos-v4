// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    HOS_MAX_TPRI API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiMaxTpri_h__
#define __HOSV4CFG_ApiMaxTpri_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TPRI ��
class CApiMaxTpri : public CApiDef
{
public:
	CApiMaxTpri();		// ���󥹥ȥ饯��
	~CApiMaxTpri();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ��ưID�ֹ�������
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�

protected:
	int m_iMaxPri;
};


#endif	// __HOSV4CFG_ApiMaxTpri_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
