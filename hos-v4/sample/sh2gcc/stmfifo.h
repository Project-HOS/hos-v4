/* ------------------------------------------------------------------------ */
/*  ���ȥ꡼��ǡ����� FIFO�Хåե�                                         */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __stmfifo_h__
#define __stmfifo_h__


/* FIFO�Хåե� */
typedef struct t_stmfifo
{
	UB  *buf;		/* �Хåե��ѥ������Ƭ���ɥ쥹 */
	INT bufsz;		/* �Хåե��ѥ���Υ����� */
	INT head;		/* �ǡ�����Ƭ���� */
	INT tail;		/* �ǡ����������� */
} T_STMFIFO;


#ifdef __cplusplus
extern "C" {
#endif

void stmfifo_cre_fifo(T_STMFIFO *this, UB *buf, INT bufsz);		/* ���󥹥ȥ饯�� */
void stmfifo_del_fifo(T_STMFIFO *this);							/* �ǥ��ȥ饯�� */

ER   stmfifo_snd_chr(T_STMFIFO *this, UB chr);					/* ������饯���񤭹��� */
ER   stmfifo_rcv_chr(T_STMFIFO *this, UB *p_chr);				/* ������饯���ɤ߹��� */

#ifdef __cplusplus
}
#endif


#endif	/* __stmfifo_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */
/* ------------------------------------------------------------------------ */
