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


/* debug�� */
#define HOS_ERCHK_ALL


/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �С��������� */
#define TKERNEL_MAKER	0x0008				/* �᡼����������(�Ŀ�) */
#define TKERNEL_PRID	0x0000				/* �����ͥ�μ����ֹ�(̤��) */
#define TKERNEL_SPVER	0x5401				/* ITRON���ͤΥС������(��ITRON Ver 4.01) */
#define TKERNEL_PRVER	0x0001				/* �����ͥ�ΥС�������ֹ� (HOS-V4 Ver 0.01) */

/* �ӥåȥѥ�����Υӥåȿ� */
#define TBIT_TEXPTN		16					/* �������㳰�װ��Υӥåȿ� */
#define TBIT_RDVPTN		16					/* ���ǥ־��Υӥåȿ� */

/* ID���ϰ� */
#define TMIN_MTXID		1					/* �ߥ塼�ƥå���ID�κǾ��� */
#define TMIN_PORID		1					/* ���ǥ�ID�κǾ��� */
#define TMIN_MPLID		1					/* ����Ĺ����ס���ID�κǾ��� */
#define TMIN_ALMID		1					/* ���顼��ϥ�ɥ�ID�κǾ��� */
#define TMIN_OVRID		1					/* �����С����ϥ�ɥ�ID�κǾ��� */


/* ���顼�����å�(HOS�ȼ�) */
#ifdef HOS_ERCHK_ALL
#define HOS_ERCHK_E_PAR						/* E_PAR �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_ID						/* E_ID �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_CTX						/* E_CTX �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_ILUSE					/* E_ILUSE �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_NOMEM					/* E_NOMEM �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_OBJ						/* E_OBJ �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_NOEXS					/* E_NOEXS �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_QOVR					/* E_QOVR �Υ��顼�����å���Ԥ� */
#endif


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
