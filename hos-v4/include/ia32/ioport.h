/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (IA32用I/Oポート処理)                  */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __hos_v4__ia32__ioport_h__
#define __hos_v4__ia32__ioport_h__
/*
 *  No I/O relevant side-effects version wait
 *  note: Instruction cache will be clean.
 */
#define __pacia32_io_nioeft_wait      "jmp 1f\n\t"     \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
                                  "1:\tjmp 2f\n\t" \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
				  "2:\tjmp 3f\n\t" \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
                                  "nop\n\t"        \
				  "3:\tjmp 4f\n\t" \
				  "4:\tnop\n\t"    \
                                  "nop\n\t"        \
                                  "nop\n\t"
/*
 *  I/O relevant side-effects version wait
 *  note: Instruction cache will not be clean.
 *        Is it true?
 */
#define __pacia32_ioeft_wait      "outb %%al,$0x80\n\t"

/*
 *  Port I/O without wait
 */
static inline void 
out_port_byte(unsigned short port, unsigned char data)
{
  __asm__ __volatile__ ("outb %b1, %w0"
			:/* No output */
			: "Nd" (port), "a" (data));
  return;
}

static inline void
out_port_word (unsigned short port, unsigned short data)
{
  asm ("outw %w1, %w0"
       :/* No output */
       : "Nb" (port), "a" (data));
  return;
}

static inline void 
out_port_dword (unsigned short port, unsigned long data)
{
  __asm__  __volatile__ ("outl %1, %w0"
			 : /* No output */
			 : "Nb" (port), "a" (data));
  return;
}

static inline unsigned char
in_port_byte(unsigned short port)
{
  unsigned char ret;

  __asm__ __volatile__ ("inb %w1, %b0"
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned short
in_port_word(unsigned short port)
{
  unsigned short ret;

  __asm__ __volatile__ ("inw %w1, %b0"
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned long
in_port_dword (unsigned short port)
{
  unsigned long ret;

  __asm__ __volatile__ ("inl %w1, %w0"
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

/*
 *  port I/O with wait without I/O relevant side-effects
 */
static inline void 
out_port_byte_with_wait(unsigned short port, unsigned char data)
{
  __asm__ __volatile__ ("outb %b1, %w0\n\t"
			__pacia32_io_nioeft_wait
			:/* No output */
			: "Nd" (port), "a" (data));
  return;
}

static inline void
out_port_word_with_wait(unsigned short port, unsigned short data)
{
  asm ("outw %w1, %w0\n\t"
       __pacia32_io_nioeft_wait
       :/* No output */
       : "Nb" (port), "a" (data));
  return;
}

static inline void 
out_port_dword_with_wait(unsigned short port, unsigned long data)
{
  __asm__  __volatile__ ("outl %1, %w0\n\t"
			 __pacia32_io_nioeft_wait
			 : /* No output */
			 : "Nb" (port), "a" (data));
  return;
}

static inline unsigned char
in_port_byte_with_wait(unsigned short port)
{
  unsigned char ret;

  __asm__ __volatile__ ("inb %w1, %b0\n\t"
			 __pacia32_io_nioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned short
in_port_word_with_wait(unsigned short port)
{
  unsigned short ret;

  __asm__ __volatile__ ("inw %w1, %b0\n\t"
			 __pacia32_io_nioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned long
in_port_dword_with_wait(unsigned short port)
{
  unsigned long ret;

  __asm__ __volatile__ ("inl %w1, %w0\n\t"
			 __pacia32_io_nioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}


/*
 *  port I/O with wait with I/O relevant side-effects
 *  It will wait about 1ms.
 */
static inline void 
out_port_byte_slow(unsigned short port, unsigned char data)
{
  __asm__ __volatile__ ("outb %b1, %w0\n\t"
			__pacia32_ioeft_wait
			:/* No output */
			: "Nd" (port), "a" (data));
  return;
}

static inline void
out_port_word_slow(unsigned short port, unsigned short data)
{
  asm ("outw %w1, %w0\n\t"
       __pacia32_ioeft_wait
       :/* No output */
       : "Nb" (port), "a" (data));
  return;
}

static inline void 
out_port_dword_slow(unsigned short port, unsigned long data)
{
  __asm__  __volatile__ ("outl %1, %w0\n\t"
			 __pacia32_ioeft_wait
			 : /* No output */
			 : "Nb" (port), "a" (data));
  return;
}

static inline unsigned char
in_port_byte_slow(unsigned short port)
{
  unsigned char ret;

  __asm__ __volatile__ ("inb %w1, %b0\n\t"
			 __pacia32_ioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned short
in_port_word_slow(unsigned short port)
{
  unsigned short ret;

  __asm__ __volatile__ ("inw %w1, %b0\n\t"
			 __pacia32_ioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

static inline unsigned long
in_port_dword_slow(unsigned short port)
{
  unsigned long ret;

  __asm__ __volatile__ ("inl %w1, %w0\n\t"
			 __pacia32_ioeft_wait
			: "=a" (ret)
			: "Nd" (port));

  return ret;
}

/*
 * String operation
 */
static inline void 
out_port_byte_string (unsigned short port, unsigned char *data, unsigned long length)
{
  __asm__ __volatile__  ("cld\n\t"
			 "rep\n\t"
			 "outsb\n\t"
			 : /* No output */
			 : "c" (length),
			 "S" (data),
			 "Nb" (port));
  return;
}

static inline void 
out_port_dword_string (unsigned short port, unsigned long *data, unsigned long length)
{
  __asm__ __volatile__   ("cld\n\t"
			  "rep\n\t"
			  "outsl\n\t"
			  : /* No output */
			  : "c" (length),
			  "S" (data),
			  "Nb" (port));
  return;
}

static inline void 
in_port_dword_string (unsigned short port, unsigned long *data, unsigned long length)
{
  __asm__ __volatile__  ("cld\n\t"
			 "rep\n\t"
			 "insl\n\t"
			 : /* No output */
			 : "c" (length),
			 "D" (data),
			 "Nb" (port));
  return;
}
#endif  /*  __hos_v4__ia32__ioport_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
