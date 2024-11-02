/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*    プロセッサ抽象化コンポーネント (IA32用)                               */
/*    アイドル処理定義                                                      */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__idle_h__
#define __HOS_V4__IA32__idle_h__

/*  アイドル時処理 
 *  電力消費低減のためにhlt命令を発行
 */
#define hospac_idle()	__asm__ __volatile__("hlt\n\t")  

#define hospac_dis_int()  __asm__ __volatile__("cli\n\t")  /* 割り込み禁止 */

#define hospac_ena_int()  __asm__ __volatile__("sti\n\t")  /* 割り込み許可 */

#endif  /*   __HOS_V4__IA32__idle_h__  */
