/* ------------------------------------------------------------------------ */
/*  SH7045 SCI����                                                          */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"
#include "sh7045.h"
#include "sci.h"
#include "stmfifo.h"



/* SCI���ɥ쥹�ơ��֥� */
volatile UB * const sci_base_adr[2] = {SH_SMR0, SH_SMR1};

/* �쥸�������������ޥ��� */
#define SH_SMR(id)		(sci_base_adr[id - 1] + 0)
#define SH_BRR(id)		(sci_base_adr[id - 1] + 1)
#define SH_SCR(id)		(sci_base_adr[id - 1] + 2)
#define SH_TDR(id)		(sci_base_adr[id - 1] + 3)
#define SH_SSR(id)		(sci_base_adr[id - 1] + 4)
#define SH_RDR(id)		(sci_base_adr[id - 1] + 5)


/* SCI���楯�饹 */
typedef struct t_sci
{
	ID flgid_snd;
	ID semid_rcv;
	T_STMFIFO sndfifo;
	T_STMFIFO rcvfifo;
	UB sndbuf[SCI_SND_BUFSZ];
	UB rcvbuf[SCI_RCV_BUFSZ];
} T_SCI;


T_SCI scicb_tbl[2];


/* ����� */
void sci_init(VP_INT exinf)
{
	T_SCI* scicb;
	int i;
	volatile int v;
	
	/* ID=1(SCI0)�ν���� */
	*SH_SCR(1) = 0x00;
	scicb_tbl[0].flgid_snd = FLGID_SCI1_SND;
	scicb_tbl[0].semid_rcv = SEMID_SCI1_RCV;
	
	/* ID=2(SCI1)�ν���� */
	*SH_SCR(2) = 0x00;
	scicb_tbl[1].flgid_snd = FLGID_SCI2_SND;
	scicb_tbl[1].semid_rcv = SEMID_SCI2_RCV;
	
	/* �����ߥ�٥������ */
	*SH_IPRF = 0x00ee;
}


/* �����ץ� */
ER sci_open(
		ID id,
		UB brr)
{
	T_SCI *scicb;
	INT i;
	volatile INT v;
	
	scicb = &scicb_tbl[id - 1];
	
	/* ��������FIFO�Хåե����� */
	stmfifo_cre_fifo(&scicb->sndfifo, scicb->sndbuf, SCI_SND_BUFSZ);
	stmfifo_cre_fifo(&scicb->rcvfifo, scicb->rcvbuf, SCI_RCV_BUFSZ);
	
	/* ����� */
	*SH_SMR(id)  = 0;
	*SH_BRR(id)  = brr;
	for ( i = 0; i < 1000; i++ )
		v++;
	*SH_SCR(id)  = SH_SCR_RIE | SH_SCR_TE | SH_SCR_RE;
	*SH_SSR(id) &= 0x80;
}


/* ������ */
ER sci_close(
		ID id)
{
	T_SCI *scicb;
	
	scicb = &scicb_tbl[id - 1];
	
	/* SCI����� */
	*SH_SCR(id) = 0x00;
	
	/* �Хåե��˴� */
	stmfifo_del_fifo(&scicb->sndfifo);
	stmfifo_del_fifo(&scicb->rcvfifo);
}


/* ��ʸ������ */
ER sci_putc(
		ID id,
		UB chr)
{
	T_SCI *scicb;
	
	scicb = &scicb_tbl[id - 1];
	
	*SH_PEDR |= 0x10;
	
	while ( stmfifo_snd_chr(&scicb->sndfifo, chr) != E_OK )
	{
		*SH_SCR(id) |= SH_SCR_TIE;	/* ���������ߵ��� */
		wai_flg(scicb->flgid_snd, 1, TWF_ANDW, NULL);
	}
	
	*SH_PEDR |= 0x20;
	
	*SH_SCR(id) |= SH_SCR_TIE;	/* ���������ߵ��� */
	
	*SH_PEDR |= 0x40;
}


/* ʸ������� */
ER_UINT sci_puts(
		ID       id,
		const UB *str)
{
	char  c;
	
	while ( c = *str++ )
	{
		sci_putc(id, c);
	}
	
	return 0;
}



/* ��ʸ������ */
ER_UINT sci_getc(
		ID id)
{
	T_SCI *scicb;
	UB chr;
	
	scicb = &scicb_tbl[id - 1];
	
	wai_sem(scicb->semid_rcv);
	stmfifo_rcv_chr(&scicb->rcvfifo, &chr);
	
	return (ER_UINT)chr;
}


/* ʸ�������� */
ER_UINT sci_gets(
		ID id,
		UB *str)
{
	INT i;
	UB  c;
	
	for ( i = 0; ; i++ )
	{
		c = sci_getc(id);
		if ( c == '\r' )
		{
			break;
		}
		str[i] = c;
	}
	
	str[i] = '\0';
	
	return i;
}


/* ���������ߥϥ�ɥ� */
void sci_snd_hdr(
		VP_INT exinf)
{
	T_SCI *scicb;
	ID    id;
	UB    chr;
	
	id    = (ID)exinf;
	scicb = &scicb_tbl[id - 1];
	
	*SH_PEDR |= 0x01;
	
	/* ����FIFO������Ф� */
	if ( stmfifo_rcv_chr(&scicb->sndfifo, &chr) != E_OK )
	{
		*SH_SCR(id) &= ~SH_SCR_TIE;	/* ������������� */
		return;
	}
	
	/* ������饯������ */
	*SH_TDR(id)  = chr;
	*SH_SSR(id) &= ~SH_SSR_TDRE;
	
	/* ������ǽ�ե饰���å� */
	set_flg(scicb->flgid_snd, 1);
}


/* ���������ߥϥ�ɥ� */
void sci_rcv_hdr(
		VP_INT exinf)
{
	T_SCI *scicb;
	ID    id;
	UB    chr;
	
	id    = (ID)exinf;
	scicb = &scicb_tbl[id - 1];
	
	*SH_PEDR |= 0x02;
	
	/* ������饯������ */
	chr = *SH_RDR(id);
	*SH_SSR(id) &= ~SH_SSR_TDRF;
	
	/* ����FIFO�Хåե����ɲ� */
	if ( stmfifo_snd_chr(&scicb->rcvfifo, chr) == E_OK )
	{
		sig_sem(scicb->semid_rcv);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */
/* ------------------------------------------------------------------------ */
