// ===========================================================================
//  HOS V4 ����ե�����졼����
//    �ѥ�᡼���������� ��ݥ��饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamType_h__
#define __HOSV4CFG_ParamType_h__


// �ѥ�᡼���������
#define PARAMTYPE_NULL			0	// ���ѥ�᡼����
#define PARAMTYPE_BLOCK			1	// �ѥ�᡼�����֥�å�
#define PARAMTYPE_AUTO_INT		2	// ��ư�����б������ͥѥ�᡼����
#define PARAMTYPE_NONAUTO_INT	3	// ��ư�������б������ͥѥ�᡼����
#define PARAMTYPE_PREPROP		4	// �ץ�ץ��å�������ѥ�᡼����
#define PARAMTYPE_GENELAL		5	// ����������ѥ�᡼����

// ���顼���������
#define PARAMTYPE_ERR_OK		0	// ����
#define PARAMTYPE_ERR_WARNING	1	// �ٹ��
#define PARAMTYPE_ERR_ERROR		2	// ���顼
#define PARAMTYPE_ERR_FATAL		3	// ��̿���顼


// �ѥ�᡼���������ץ��饹
class CParamType
{
public:
	virtual ~CParamType();	// �ǥ��ȥ饯��

	virtual int GetParamType() = 0;		// �������׼���

	virtual int SetParamString(const char* pszParam) = 0;	// �ѥ�᡼����ʸ���������
	
	virtual const char* GetParamString(void) = 0;			// �ѥ�᡼����ʸ����μ���
	virtual int GetParamInt(void) = 0;						// �ѥ�᡼�����������ͼ���
};


#endif	// __HOSV4CFG_ParamType_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
