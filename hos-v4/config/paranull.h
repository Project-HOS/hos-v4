// ===========================================================================
//  HOS V4 ����ե�����졼����
//    NULL�ѥ�᡼�������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamNull_h__
#define __HOSV4CFG_ParamNull_h__


#include "paratype.h"


// �ѥ�᡼�����֥�å����饹
class CParamNull : public CParamType
{
public:
	int GetParamType();			// �������׼���

	int SetParamString(const char* pszParam);	// �ѥ�᡼����ʸ���������
	const char* GetParamString(void);			// �ѥ�᡼����ʸ����μ���
	int GetParamInt(void);						// �ѥ�᡼�����������ͼ���
};


#endif	// __HOSV4CFG_ParamNull_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
