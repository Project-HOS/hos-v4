// ===========================================================================
//  HOS V4 ����ե�����졼���� Ver 1.00
//    �ǡ����ɤ߹��ߥ��饹
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ===========================================================================



#ifndef __HOSV4CFG_Read_h__
#define __HOSV4CFG_Read_h__


#define READ_MAX_STATE		4096	// �����ơ��Ȥκ���ʸ����


// ��ʸ���ϥ��饹
class CRead
{
public:
	CRead(FILE *fp);				// ���󥹥ȥ饯��
	~CRead();						// �ǥ��ȥ饯��

	int ReadState(char *szState);	// �����ơ����ɤ߹���
	int GetLineNum(void)			// ���ߤι��ֹ����
	{ return m_iLineNum; }

protected:
	int SkipPriProcessorLine(void);	// �ץ�ץ��å��饤��Υ����å�
	int ReadString(int cDelimiter, char* szText, int& iCount);	// ʸ�����ɤ߹���

	FILE *m_fpRead;					// �ɤ߹����ѥե�����ݥ���
	int  m_iLineNum;				// ���ߤι��ֹ�
	bool m_blLineTop;				// �Ԥ���Ƭ
};


#endif	// __HOSV4CFG_Read_h__


// ===========================================================================
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ===========================================================================
