/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネルコンフィギュレーション ID定義ファイル                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__kernel_id_h__
#define __HOS_V4__kernel_id_h__


/* システム設定 */
#define TIC_NUME		10		/* タイムティックの分子 */
#define	TIC_DENO		1		/* タイムティックの分母 */


/* タスクID */
#define TSKID_TEST1		1
#define TSKID_TEST2		2
#define TSKID_TEST3		3

/* セマフォID */
#define SEMID_TEST1		1
#define SEMID_TEST2		2

/* イベントフラグID */
#define FLGID_TEST1		1
#define FLGID_TEST2		2

/* データキューID */
#define DTQID_TEST1		1
#define DTQID_TEST2		2




#endif	/* __HOS_V4__kernel_id_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
