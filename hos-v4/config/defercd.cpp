// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    ���顼�����ɴ���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include "defercd.h"


static const char *szErrMsg[] =
	{
		"unanticipated EOF.",		// ͽ������EOF
		"illegal CR.",				// �����ʲ���
		"status too long.",			// �����ơ��Ȥ�Ĺ������
		"syntax error."	,			// ��ʸ���顼
		"expect \')\' but found.",	// ()��������
		"expect \'}\' but found.",	// {}��������
		"expect \';\' but found.",	// ���ߥ�����̵��
		"illegal text.",			// ������ʸ�������
		"conflict ID.",				// ID����
		"illegal parameter",		 // �ѥ�᡼��������
	};


// ���顼ʸ�������
const char* GetErrMessage(int iErr)
{
	if ( iErr < 1 || iErr > 10 )
	{
		return "";
	}

	return szErrMsg[iErr - 1];
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------