// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    HOS_KERNEL_HEAP API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_KernelHeap_h__
#define __HOSV4CFG_KernelHeap_h__


#include "apidef.h"
#include "parpack.h"


// HOS_KERNEL_HEAP ��
class CApiKernelHeap : public CApiDef
{
public:
	CApiKernelHeap();		// ���󥹥ȥ饯��
	~CApiKernelHeap();		// �ǥ��ȥ饯��

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// API�β���
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);		// cfg�ե�����������񤭽Ф�
	void  WriteCfgStart(FILE* fp);		// cfg�ե����뵯ư���񤭽Ф�
};


#endif	// __HOSV4CFG_KernelHeap_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
