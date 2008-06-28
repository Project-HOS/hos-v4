#include	<semb1200a/semb1200a.h>
#include	<semb1200a/ux_signal.h>
#include	<string.h>

#define		INT_ADDRESS		(0xA0000180)
#define		INT_VECTOR		(0xA0000600)
#define		INT_HANDLER		(0xA0000800)

/*
 *  crt0.c for SEMB1200A
 */
asm("	.text						\n"
	"	.align	4					\n"
	"	.global	_start				\n"
	"	.ent	_start				\n"
	"_start:						\n"
	"	la		$29, _stack_init	\n"
	"	la		$28, _gp			\n"
	"	mfc0	$2,  $12			\n"
	"	lui		$3,  0x0400			\n"
	"	not		$3					\n"
	"	and		$2,  $3				\n"
	"	mtc0	$2,  $12			\n"
	"	nop							\n"
	"	nop							\n"
	"	j		_start1				\n"
	"	nop							\n"
	"	.end	_start				\n" );

/*
 *  cache (8byte)
 */
#define	cache8(fadrs)	({						\
			register int __adrs;				\
			__asm__ __volatile__ (				\
				"li		%0,"STR(fadrs)"\n\t"	\
				"cache	4,0(%0)\n\t"			\
				"cache	4,1(%0)\n\t"			\
				"cache	4,2(%0)\n\t"			\
				"cache	4,3(%0)\n\t"			\
				"cache	4,4(%0)\n\t"			\
				"cache	4,5(%0)\n\t"			\
				"cache	4,6(%0)\n\t"			\
				"cache	4,7(%0)\n\t"			\
				"nop"							\
				: "=r" (__adrs));				\
		})
/*
 *  inline memcpy(), memset()
 */
void	__crt0_memcpy(
	char	*dst,
	char	*src,
	int		len
)
{
	while( len-- > 0 ) {
		*dst++ = *src++;
	}
}
void	__crt0_memset(
	char	*des,
	int		c,
	int		len
)
{
	while( len-- > 0 ) {
		*des++ = (char)c;
	}
}
void	_start1( void )
{
	extern	int		main( void );
	extern	char	inthdl[], einthdl[], inthdljp[];
	extern	char	_erdata[], _data[], _edata[];
	extern	char	_fbss[], _end[];

	__crt0_memcpy( _data, _erdata, (size_t)_edata - (size_t)_data );
	__crt0_memset( _fbss, 0, (size_t)_end - (size_t)_fbss );

	__crt0_memset( (char*)INT_VECTOR, 0, INT_HANDLER-INT_VECTOR );
	__crt0_memcpy( (char*)INT_HANDLER, inthdl, (size_t)einthdl - (size_t)inthdl );
	__crt0_memcpy( (char*)INT_ADDRESS, inthdljp, 8 );
	cache8( INT_ADDRESS );
	main();
}
