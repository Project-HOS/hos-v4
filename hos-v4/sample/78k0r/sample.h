/*******************************************************************************
 * Hyper Operating System V4  サンプルプログラム
 *
 *                                      Copyright (C) 1998-2007 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/
#ifndef __SAMPLE_H__
#define __SAMPLE_H__

typedef	unsigned char	uint8;
typedef	unsigned short	uint16;
typedef	unsigned long	uint32;

typedef	char		int8;
typedef	short		int16;
typedef	long		int32;

void	uart2_putc( uint8 );
uint8	uart2_getc( void );
void	uart2_puts( int8 * );
void	sample_init (VP_INT exinf);
void	sample_task_1 (VP_INT exinf);
void	sample_task_2 (VP_INT exinf);
void	sample_print (int no);
void	sample_cycle_handler (VP_INT exinf);

#endif /* __SAMPLE_H__ */
