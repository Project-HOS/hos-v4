// ===========================================================================
//  HOS V4 ����ե�����졼����
//    API������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_DefApi_h__
#define __HOSV4CFG_DefApi_h__


#include "parablk.h"


// API�����¤��
struct TDefApi
{
	const char*  pszApiName;		// API̾
	CParamBlock* pParamBlock;		// �ѥ�᡼�����֥�å�
	TDefApi*     pNext;				// ����API���
};


// API����������饹
class CDefApi
{
public:
	CDefApi();
	~CDefApi();

	void AddDefine(TDefApi* pDefApi);				// API������ɲ�
	TDefApi* GetDefine(const char* pszApiName);		// API����μ���

protected:
	TDefApi* m_pDefApi;
};


#endif	// __HOSV4CFG_DefApi_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
