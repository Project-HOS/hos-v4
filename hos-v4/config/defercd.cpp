// ---------------------------------------------------------------------------
//  Hyper Operating System V4  ����ե�����졼����                           
//    ���顼�����ɴ���                                                        
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
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
		"expect \';\' but found.",	// ���ߥ����̵��
		"illegal text.",			// ������ʸ�������
		"conflict ID.",				// ID����
		"illegal parameter.",		 // �ѥ�᡼��������
		"multiple definition.",		// ͣ��Ǥ���٤�API�����ʣ��
		"conflict definition.",		 // �������
	};


// ���顼ʸ�������
const char* GetErrMessage(int iErr)
{
	if ( iErr < 1 || iErr > (int)(sizeof(szErrMsg)/sizeof(char *)) )
	{
		return "unknown expression error.";
	}

	return szErrMsg[iErr - 1];
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
