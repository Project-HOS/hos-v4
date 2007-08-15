#include <semb1200a/semb1200a.h>
#include "semb1200a/ux_signal.h"

// キャッシュを不使用にする
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

    // DATA領域のコピー
    memcpy( _data, _erdata, (size_t)_edata - (size_t)_data );
    // FBSS領域の初期化
    memset( _fbss, 0, (size_t)_end - (size_t)_fbss );
    // キャッシュ不使用を試す
    cache_off ();

    //uart1_putc ('1');
    // 割り込みハンドラの登録（無理矢理コピー）
    // 一般例外アドレス(キャッシュなし）
    p = (int*)0xA0000180;
    for (i=0; i<400; i++) {
        p[i] = *((int *)int_handler + i);
    }
    // メインルーチンの呼び出し
    main();
}
