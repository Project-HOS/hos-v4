// ===========================================================================
//  HOS V4 ����ե�����졼���� Ver 1.00
//    �ǡ����ɤ߹��ߥ��饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================



#ifndef __HOSV4CFG_Read_h__
#define __HOSV4CFG_Read_h__



// ��ʸ���ϥ��饹
class CRead
{
public:
	static void ReadConfig(FILE* fpIn, FILE* fpOut);	// ����ե�����졼�����ե�������ɤ߹���

protected:
	static void  Analize(void);

	static char* m_pFileText;		// ����ե�����졼�����ե�����ǡ���
	static int   m_iFileSize;		// ����ե�����졼�����ե����륵����
	static int   m_iLineNum;		// ���ֹ�
};


#endif	// __HOSV4CFG_Read_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
