/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå�                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__kernel_h__
#define __HOS_V4__kernel_h__



#include <stddef.h>
#include "itron.h"
#include "mknl.h"
#include "hoserchk.h"


/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

#define TBIT_RDVPTN		16					/* ���ǥ־��Υӥåȿ� */

/* ID���ϰ� */
#define TMIN_MTXID		1					/* �ߥ塼�ƥå���ID�κǾ��� */
#define TMIN_PORID		1					/* ���ǥ�ID�κǾ��� */
#define TMIN_MPLID		1					/* ����Ĺ����ס���ID�κǾ��� */
#define TMIN_ALMID		1					/* ���顼��ϥ�ɥ�ID�κǾ��� */
#define TMIN_OVRID		1					/* �����С����ϥ�ɥ�ID�κǾ��� */



/* C++ �� static_cast �黻�Ҥ�Ʊ�����̤Υޥ��� */
#define KERNEL_STATIC_CAST(s, m, p)	((s *)((B*)(p))-offsetof(s, m))	/* ���ФΥ��ɥ쥹���鹽¤�ΤΥ��ɥ쥹���� */

/* C����ι�¤�Τ��Ѥ��ƥݥ�⡼�ե������¸�����ݤ� */
/* ��¤�Υ��ФΥݥ��󥿤��顢��¤����Ƭ�Υݥ��󥿤�  */
/* ���Ф��뤳�Ȥ�ɬ�ܤȤʤ롣�嵭�� C++ ����Ǥ�       */
/* dynamic_cast �� static_cast �黻�Ҥǰ����˹Ԥ��뤬  */
/* C����ǤϤ������ٶ����˼�������ɬ�פ����롣         */


#include "knl_hos.h"
#include "knl_tsk.h"
#include "knl_sem.h"
#include "knl_flg.h"
#include "knl_dtq.h"
#include "knl_mbx.h"
#include "knl_mpf.h"
#include "knl_tim.h"
#include "knl_sys.h"
#include "knl_int.h"
#include "knl_exc.h"


/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif


/* �ߥ塼�ƥå��� */
ER      loc_mtx(ID mtxid);							/* �ߥ塼�ƥå����Υ�å� */
ER      ploc_mtx(ID mtxid);							/* �ߥ塼�ƥå����Υ�å�(�ݡ����) */
ER      tloc_mtx(ID mtxid);							/* �ߥ塼�ƥå����Υ�å�(�����ॢ���Ȥ���) */
ER      unl_mtx(ID mtxid);							/* �ߥ塼�ƥå����Υ�å���� */

/* ��å������Хåե� */
ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);		/* ��å������Хåե��ؤ����� */
ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);		/* ��å������Хåե��ؤ�����(�ݡ����) */
ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);
													/* ��å������Хåե��ؤ�����(�����ॢ���Ȥ���) */



#ifdef __cplusplus
}
#endif



#endif /* __HOS_V4__kernel_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
