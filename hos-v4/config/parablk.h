// ===========================================================================
//  HOS V4 ����ե�����졼����
//    �ѥ�᡼�����֥�å��������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamBlock_h__
#define __HOSV4CFG_ParamBlock_h__


#include "paratype.h"


// �ѥ�᡼�����֥�å����饹
class CParamBlock : public CParamType
{
public:
	CParamBlock(int iMaxParam, int iMinParam);		// ���󥹥ȥ饯��
	~CParamBlock();									// �ǥ��ȥ饯��

	int GetParamType();		// �������׼���

	int SetParamString(const char* pszParam);		// �ѥ�᡼����ʸ���������

	void SetParam(int iIndex, CParamType* pParamType);	// �ѥ�᡼����������
	CParamType* GetParam(int iIndex);					// �ѥ�᡼�����μ���

protected:
	CParamType** m_ppPramList;		// �ѥ�᡼�����ꥹ��
	int m_iMaxParam;				// ����ѥ�᡼������
	int m_iMinParam;				// �Ǿ��ѥ�᡼������
};


#endif	// __HOSV4CFG_ParamBlock_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
