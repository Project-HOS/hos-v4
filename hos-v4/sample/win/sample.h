/* ------------------------------------------------------------------------ */
/*  HOS-V4 ����ץ�                                                         */
/*   �ᥤ��롼����                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __sample_h__
#define __sample_h__


/* ů�ؼԥ������ȥե��������ޥե���ID������ͤǻ��� */
#define TSKID_PHILOSOPHER1	1
#define TSKID_PHILOSOPHER2	2
#define TSKID_PHILOSOPHER3	3
#define TSKID_PHILOSOPHER4	4
#define TSKID_PHILOSOPHER5	5
#define SEMID_FORK1			1
#define SEMID_FORK2			2
#define SEMID_FORK3			3
#define SEMID_FORK4			4
#define SEMID_FORK5			5


#ifdef __cplusplus
extern "C" {
#endif

void SampleInitialize(VP_INT exinf);	/* ATT_INI ��Ͽ�δؿ� */
void PhilosopherTask(VP_INT exinf);		/* ů�ؼԥ����� */


#ifdef __cplusplus
}
#endif



#endif	/* __sample_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
