// ===========================================================================
//  HOS V4 ����ե�����졼����
//    NULL�ѥ�᡼�������饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include "paranull.h"


// �������׼���
int CParamNull::GetParamType()
{
	return PARAMTYPE_NULL;
}


// �ѥ�᡼����ʸ���������
int CParamNull::SetParamString(const char* pszParam)
{
	return PARAMTYPE_ERR_OK;
}


// �ѥ�᡼����ʸ����μ���
const char* CParamNull::GetParamString(void)
{
	return "";
}


// �ѥ�᡼�����������ͼ���
int CParamNull::GetParamInt(void)
{
	return 0;
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
