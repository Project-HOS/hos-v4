#include <semb1200a/semb1200a.h>
#include "semb1200a/ux_signal.h"

// $B%-%c%C%7%e$rIT;HMQ$K$9$k(B
void
cache_off (void)
{
	unsigned long	tmp;
    unsigned long   off = 0x00000010;
    unsigned long   mask =0x00000038;

	tmp = read_32bit_cp0_register( CP0_ENTRYLO0);
	tmp &= ~mask;
    tmp |= off;
	write_32bit_cp0_register( CP0_ENTRYLO0, tmp );

	tmp = read_32bit_cp0_register( CP0_ENTRYLO1);
	tmp &= ~mask;
    tmp |= off;
	write_32bit_cp0_register( CP0_ENTRYLO1, tmp );
}

/*
 *  crt0.c for SEMB1200A
 */
#if 1
// $29: stack pointer
// $28: gp (?)
asm( "  .text\n"
     "  .align      2\n"
     "  .global     _start      \n"
     "  .ent        _start      \n"
     "_start:               \n"
     "  la  $29,    _stack_init \n"
     "  la  $28,    _gp     \n"
     "  j   _start1         \n"
     "  .end    _start          \n" );
#endif

#include    <string.h>

extern int main (void);
extern void int_handler (void);

void
_start1( void )
{
    int i;
    volatile int *p;
    extern  char    _erdata[], _data[], _edata[];
    extern  char    _fbss[], _end[];

    // DATA$BNN0h$N%3%T!<(B
    memcpy( _data, _erdata, (size_t)_edata - (size_t)_data );
    // FBSS$BNN0h$N=i4|2=(B
    memset( _fbss, 0, (size_t)_end - (size_t)_fbss );
    // $B%-%c%C%7%eIT;HMQ$r;n$9(B
    cache_off ();

    //uart1_putc ('1');
    // $B3d$j9~$_%O%s%I%i$NEPO?!JL5M}LpM}%3%T!<!K(B
    // $B0lHLNc30%"%I%l%9(B($B%-%c%C%7%e$J$7!K(B
    p = (int*)0xA0000180;
    for (i=0; i<400; i++) {
        p[i] = *((int *)int_handler + i);
    }
    // $B%a%$%s%k!<%A%s$N8F$S=P$7(B
    main();
}
