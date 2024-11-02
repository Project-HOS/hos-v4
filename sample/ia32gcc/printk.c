/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*    簡易コンソール出力                                                    */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "printk.h"
#ifdef __STDC__
#include "stdarg.h"
#else
#include "varargs.h"
#endif
#define isdigit(c) ( ('0' <= c) || (c <= '9') 
#define __sta_crit(flags)  do{                          \
       __asm__ __volatile__ ("pushfl\n\t"               \
                             "popl %0\n\t"              \
                             "cli\n\t"                  \
			     :"=m"(flags));             \
    }while(0)

#define __end_crit(flags) do{                           \
       __asm__ __volatile__ ("pushl %0\n\t"             \
			     "popfl\n\t"                \
			     ::"m"(flags));             \
   }while(0)

/*  X position.  */
int xpos;
/*  Y position.  */
int ypos;
/* Pointer to the video memory.  */
static volatile unsigned char *video;
/*  #define DEBUG_RAWSCR  */
#if defined(DEBUG_RAWSCR)
static char debug_ram[80*25*2];
#endif 


/* Non-zero for big-endian systems.  */
static int big_endian_p;
#if 1
static void do_scroll(void);
#endif
static long get_number(char *s, long size, int unsigned_p);
static void print_number (int base, int unsigned_p, long n);


#if 1
static void
do_scroll(void)
{
  int cx,cy;
  long flags;

#if !defined(DEBUG_RAWSCR)
  video = (unsigned char *) VRAM_ADDR;
#else
  video = (unsigned char *) debug_ram;
#endif  
  __sta_crit(flags);
  for(cx = 0; cx < COLUMNS; ++cx)
    for(cy = 0; cy < LINES-1; ++cy)
      {
	/*  最期の1行を除いて表示  */
	*(video + (cx + cy * COLUMNS) * 2)  = *(video + (cx + (cy+1) * COLUMNS) * 2) ;
	*(video + (cx + cy * COLUMNS) * 2 + 1) = *(video + (cx + (cy + 1) * COLUMNS) * 2 + 1) ;
	
      }
  for(cx = 0; cx < COLUMNS; ++cx) {
    /*  行クリア  */
    locate(cx,LINES-1);
    *(video + (cx + (LINES-1) * COLUMNS) * 2) =  0x0;
    *(video + (cx + (LINES-1) * COLUMNS) * 2 + 1) = ATTRIBUTE;
  }
  __end_crit(flags);
  /* カーソル移動  */
  locate(0,LINES-1);

}
#endif

void
locate(int x,int y)
{
#ifdef CONFIG_CURSOR_MOVE
  unsigned short vram_pos = (y * COLUMNS) + x;
#endif
  long flags;

  __sta_crit(flags);

  /*  本当は, 引数チェックをしないとまずい  */
  xpos = x;
  ypos = y;

  /* カーソル移動  */
#ifdef CONFIG_CURSOR_MOVE
  out_port_byte (MC6845_INDEX_REG, 0x0F); /* set low-order address of cursor */
  out_port_byte (MC6845_DATA_REG, (unsigned char)(vram_pos & 0xFF)); 
  out_port_byte (MC6845_INDEX_REG, 0x0E); /* set high-order address of cursor */
  out_port_byte (MC6845_DATA_REG, (unsigned char)((vram_pos >> 8) & 0xFF));
#endif  /*  CONFIG_CURSOR_MOVE  */
  __end_crit(flags);
}

/* 
 *  画面消去関数
 */
void
cls (void)
{
  int i;
  long flags;

#if !defined(DEBUG_RAWSCR)
  video = (unsigned char *) VRAM_ADDR;
#else
  video = (unsigned char *) debug_ram;
#endif  
  __sta_crit(flags);
  /*  ブランクを書き込む  */
  for (i = 0; i < COLUMNS * LINES * 2; i++)
    *(video + i) = 0;
  __end_crit(flags);
  /*  ポジションを戻す  */
  locate(0,0);


  return;
}

/* Put the character C on the screen.  */
void
putchar (int c)
{
  long flags;
#if !defined(DEBUG_RAWSCR)
  video = (unsigned char *) VRAM_ADDR;
#else
  video = (unsigned char *) debug_ram;
#endif  
  __sta_crit(flags);
  if (c == '\n' || c == '\r')
    {
    newline:
      xpos = 0;
      ypos++;
      if (ypos == LINES)
	do_scroll();
      __end_crit(flags);
      return;
    }
  *(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
  *(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

  xpos++;
  if (xpos >= COLUMNS)
    goto newline;
  __end_crit(flags);
  locate(xpos,ypos);

}

void
print_string(const char *str)
{
  char *p=(char *)str;

  while(*p){
    putchar ((int)*p++);
  }
  return;
}

/* Standalone printf routine.

   The format string has been enhanced so that multiple values can be dumped
   without having to have a %-field for each one (say if you want to dump
   20 words at a certain address).  A modifier of `N' says the next argument
   is a count, and the one after that is a pointer.

   Example: low_printk (stderr, "%Nx\n", 20, p); /-* print 20 ints at `p' *-/

   Supported formats are: c d u x s p.

   All ints are retrieved a byte at a time so alignment issues are not
   a problem.

   This routine is used in situations where the only debugging capability
   is console output and was written to aid debugging newlib itself.  We don't
   use printf ourselves as we may be debugging it.  We do assume _write_r is
   working.
*/

void
#ifdef __STDC__
printk (const char *fmt, ...)
#else
printk (fmt, va_alist)
     char *fmt;
     va_dcl
#endif
{
  va_list args;
  long flags;

  __sta_crit(flags);

  /* Which endian are we?  */
  {
    short tmp = 1;
    big_endian_p = *(char *) &tmp == 0;
  }

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
#endif

  while (*fmt)
    {
      char c, *p;
      int count;
      long l;

      if (*fmt != '%' || *++fmt == '%')
	{
	  putchar (*fmt++);
	  continue;
	}

      if (*fmt == 'N')
	{
	  count = va_arg (args, int);
	  p = va_arg (args, char *);
	  ++fmt;
	  c = *fmt++;

	  while (--count >= 0)
	    {
	      switch (c)
		{
		case 'c' :
		  putchar(*p++);
		  break;
		case 'p' :
		  print_number (16, 1, get_number (p, sizeof (char *), 1));
		  p += sizeof (char *);
		  break;
		case 'd' :
		case 'u' :
		case 'x' :
		  print_number (c == 'x' ? 16 : 10, c != 'd',
				get_number (p, sizeof (int), c != 'd'));
		  p += sizeof (int);
		  break;
		case 's' :
		  print_string (*(char **) p);
		  p += sizeof (char *);
		  break;
		}
	      if (count > 0)
		putchar (' ');
	    }
	}
      else
	{
	  switch (c = *fmt++)
	    {
	    case 'c' :
	      c = va_arg (args, int);
	      putchar(c);
	      break;
	    case 'p' :
	      l = (long) va_arg (args, char *);
	      print_number (16, 1, l);
	      break;
	    case 'd' :
	    case 'u' :
	    case 'x' :
	      l = va_arg (args, int);
	      print_number (c == 'x' ? 16 : 10, c != 'd', l);
	      break;
	    case 's' :
	      p = va_arg (args, char *);
	      print_string (p);
	      break;
	    }
	}
    }

  va_end (args);
  __end_crit(flags);
}

/* Fetch the number at S of SIZE bytes.  */

static long
get_number (s, size, unsigned_p)
     char *s;
     long size;
     int unsigned_p;
{
  long x;
  unsigned char *p = (unsigned char *) s;

  switch (size)
    {
    case 1 :
      x = *p;
      if (!unsigned_p)
	x = (x ^ 0x80) - 0x80;
      return x;
    case 2 :
      if (big_endian_p)
	x = (p[0] << 8) | p[1];
      else
	x = (p[1] << 8) | p[0];
      if (!unsigned_p)
	x = (x ^ 0x8000) - 0x8000;
      return x;
    case 4 :
      if (big_endian_p)
	x = ((long)p[0] << 24) | ((long)p[1] << 16) | (p[2] << 8) | p[3];
      else
	x = ((long)p[3] << 24) | ((long)p[2] << 16) | (p[1] << 8) | p[0];
      if (!unsigned_p)
	x = (x ^ 0x80000000L) - 0x80000000L;
      return x;
#if 0 /* FIXME: Is there a standard mechanism for knowing if
	 long longs exist?  */
    case 8 :
#endif
    default :
      return 0;
  }
}

/* Print X in base BASE.  */

static void
print_number (base, unsigned_p, n)
     int base;
     int unsigned_p;
     long n;
{
  static const char chars[16] = "0123456789abcdef";
  char *p, buf[32];
  unsigned long x;

  if (!unsigned_p && n < 0)
    {
      putchar ('-');
      x = -n;
    }
  else
    x = n;

  p = buf + sizeof (buf);
  *--p = '\0';
  do
    {
      *--p = chars[x % base];
      x /= base;
    }
  while (x != 0);

  print_string (p);
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
