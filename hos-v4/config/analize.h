// ===========================================================================
//  HOS V4 ����ե�����졼����
//    ��ʸ���ϥ��饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_Analize_h__
#define __HOSV4CFG_Analize_h__


// ��ʸ���ϥ��饹
class CAnalize
{
public:
	static char* SearchBrace(char* pStr);			// '{'���б�����'}'�θ���
	static char* SearchParentheses(char* pStr);		// '('���б�����')'�θ���
	static char* SearchComma(char* pStr);			// ����','�򸡺�
	static void  NormalizerSpace(char* pStr);		// ����ʸ��������������
};


#endif	// __HOSV4CFG_Analize_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
