/* ------------------------------------------------------------------------ */
/*  HOS-V4 ����ץ�                                                         */
/*   �ᥤ��롼����                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __Ryuz__test_h__
#define __Ryuz__test_h__



#ifdef __cplusplus
extern "C" {
#endif

void TestStart(VP_INT exinf);	/* ATT_INI ��Ͽ�δؿ� */

void Task1(VP_INT exinf);		/* ����ץ륿����1 */
void Task2(VP_INT exinf);		/* ����ץ륿����2 */
void Task3(VP_INT exinf);		/* ����ץ륿����3 */

void CycHandler1(VP_INT exinf);	/* �����ϥ�ɥ饵��ץ� */

void IntHndler1(VP_INT exinf);	/* �����ߥϥ�ɥ饵��ץ� */

#ifdef __cplusplus
}
#endif



#endif	/* __Ryuz__test_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
