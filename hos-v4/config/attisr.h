// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    ATT_ISR API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_AttIsr_h__
#define __HOSV4CFG_AttIsr_h__


#include "apidef.h"
#include "parpack.h"


// ATT_ISR ��
class CApiAttIsr : public CApiDef
{
public:
	CApiAttIsr();		// ���󥹥ȥ饯��
	~CApiAttIsr();		// �ǥ��ȥ饯��

	char* GetApiName(void);						// API̾����
	int   AutoId(void);
	void  WriteCfgIni(FILE* fp);				// cfg�ե������������񤭽Ф�
};


#endif	// __HOSV4CFG_AttIsr_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
