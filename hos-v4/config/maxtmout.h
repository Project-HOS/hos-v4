// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    HOS_MAX_TPRI API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiMaxTimout_h__
#define __HOSV4CFG_ApiMaxTimout_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TIMOUT ��
class CApiMaxTimout : public CApiDef
{
public:
	CApiMaxTimout();		// ���󥹥ȥ饯��
	~CApiMaxTimout();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);							// ��ưID�ֹ�������
	void  WriteCfgDef(FILE* fp);				// cfg�ե�����������񤭽Ф�

protected:
	int m_iMaxTimout;
};


#endif	// HOSV4CFG_ApiMaxTimout


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
