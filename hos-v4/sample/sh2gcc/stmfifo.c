/* ------------------------------------------------------------------------ */
/*  ���ȥ꡼��ǡ����� FIFO�Хåե�                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "stmfifo.h"



/* ���󥹥ȥ饯�� */
void stmfifo_cre_fifo(
		T_STMFIFO *this,	/* FIFO�Хåե����饹�Υݥ��� */
		UB        *buf,		/* ������Ƥ�Хåե�����Υ��ɥ쥹 */
		INT       bufsz)	/* ������Ƥ�Хåե�����Υ����� */
{
	this->buf   = buf;
	this->bufsz = bufsz;
	this->head  = 0;
	this->tail  = 0;
}


/* �ǥ��ȥ饯�� */
void stmfifo_del_fifo(
		T_STMFIFO *this)	/* FIFO�Хåե����饹�Υݥ��� */
{
	/* �ä˽�����̵�� */
}



/* ������饯���񤭹��� */
ER stmfifo_snd_chr(
		T_STMFIFO *this,	/* FIFO�Хåե����饹�Υݥ��� */
		UB        chr)		/* �񤭹��७��饯�� */
{
	INT next_tail;
	
	/* �����������ַ׻� */
	if ( this->tail + 1 < this->bufsz )
	{
		next_tail = this->tail + 1;
	}
	else
	{
		next_tail = 0;		/* ��󥰥Хåե������ʤ��ޤ��֤� */
	}
	
	/* �Хåե��ե�Υ����å� */
	if ( next_tail == this->head )
	{
		return E_TMOUT;
	}
	
	/* �ǡ������ɲ� */
	this->buf[this->tail] = chr;
	this->tail = next_tail;
	
	return E_OK;
}


/* ������饯���ɤ߹��� */
ER stmfifo_rcv_chr(
		T_STMFIFO *this,	/* FIFO�Хåե����饹�Υݥ��� */
		UB        *p_chr)	/* ������饯�����ɤ߹���ݥ��� */
{
	/* �Хåե�����ץƥ����Υ����å� */
	if ( this->head == this->tail )
	{
		return E_TMOUT;
	}
	
	/* �ǡ������ɤ߽Ф� */
	*p_chr = this->buf[this->head];
	
	/* ������Ƭ���֤����� */
	if ( this->head + 1 < this->bufsz )
	{
		this->head = this->head + 1;
	}
	else
	{
		this->head = 0;
	}
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
