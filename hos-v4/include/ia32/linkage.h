/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*    プロセッサ抽象化コンポーネント (IA32用)                                    */
/*                                  アセンブラ用マクロ                         */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__linkage_h__
#define __HOS_V4__IA32__linkage_h__
#define SYMBOL_NAME(X) X

#ifdef __STDC__
#define SYMBOL_NAME_LABEL(X) X##:
#else
#define SYMBOL_NAME_LABEL(X) X/**/:
#endif

#define __ALIGN .align 4,0x90
#define __ALIGN_STR ".align 4,0x90"

#define ALIGN __ALIGN
#define ALIGN_STR __ALIGN_STR

#define ENTRY(name) \
  .globl SYMBOL_NAME(name); \
  ALIGN; \
  SYMBOL_NAME_LABEL(name)	
#define WVAR(name)  \
  .globl SYMBOL_NAME(name); \
  SYMBOL_NAME_LABEL(name) .long	0 


#endif  /*  __HOS_V4__IA32__linkage_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
