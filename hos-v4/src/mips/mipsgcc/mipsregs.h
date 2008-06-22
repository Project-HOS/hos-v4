/*******************************************************************************
 *
 *  プロセッサレジスタ定義
 *
 *                                  Copyright (C) 1998-2008 by Project HOS
 *                                  http://sourceforge.jp/projects/hos/
 *******************************************************************************/

/***************************************
 *  CPUコアののレジスタ番号定義
 ***************************************/
#define zero    $0
#define at      $1
#define v0      $2
#define v1      $3
#define a0      $4
#define a1      $5
#define a2      $6
#define a3      $7

#define t0      $8
#define t1      $9
#define t2      $10
#define t3      $11
#define t4      $12
#define t5      $13
#define t6      $14
#define t7      $15

#define s0      $16
#define s1      $17
#define s2      $18
#define s3      $19
#define s4      $20
#define s5      $21
#define s6      $22
#define s7      $23

#define t8      $24
#define t9      $25
#define k0      $26
#define k1      $27
#define gp      $28
#define sp      $29
#define fp      $30
#define ra      $31

/***************************************
 *  コプロセッサ0のレジスタ番号定義
 ***************************************/
#define CP0_INDEX       $0
#define CP0_RANDOM      $1
#define CP0_ENTRYLO0    $2
#define CP0_ENTRYLO1    $3
#define CP0_CONF        $3
#define CP0_CONTEXT     $4
#define CP0_PAGEMASK    $5
#define CP0_WIRED       $6
#define CP0_INFO        $7
#define CP0_BADVADDR    $8
#define CP0_COUNT       $9
#define CP0_ENTRYHI     $10
#define CP0_COMPARE     $11
#define CP0_STATUS      $12
#define CP0_CAUSE       $13
#define CP0_EPC         $14
#define CP0_PRID        $15
#define CP0_CONFIG      $16
#define CP0_LLADDR      $17
#define CP0_WATCHLO     $18
#define CP0_WATCHHI     $19
#define CP0_XCONTEXT    $20
#define CP0_FRAMEMASK   $21
#define CP0_DIAGNOSTIC  $22
#define CP0_DEBUG       $23
#define CP0_DEPC        $24
#define CP0_PERFORMANCE $25
#define CP0_ECC         $26
#define CP0_CACHEERR    $27
#define CP0_TAGLO       $28
#define CP0_TAGHI       $29
#define CP0_ERROREPC    $30
#define CP0_DESAVE      $31

/***************************************
 *  レジスタ退避マクロ
 ***************************************/

.macro	pushall
		move	k0, sp			/* 伸張前のスタックポインタを退避 */
		subu	sp, sp, 288		/* スタックフレーム確保（4*72=288バイト）*/
		sw		k0, 29*4(sp)	// sp

		.set	push
		.set	noat
		sw		$1, 1*4(sp)
		.set	pop

		sw		v1, 3*4(sp)
		mfc0	v1, CP0_STATUS
		sw		v0, 2*4(sp)
		sw		v1, 36*4(sp)	// STATUS
		sw		a0,  4*4(sp)
		mfc0	v1, CP0_CAUSE
		sw		a1,  5*4(sp)
		sw		v1, 37*4(sp)	// CAUSE
		sw		a2,  6*4(sp)
		mfc0	v1, CP0_EPC
		sw		a3,  7*4(sp)
		sw		v1, 34*4(sp)	// EPC
		sw		t0,  8*4(sp)
		sw		t1,  9*4(sp)
		sw		t2, 10*4(sp)
		sw		t3, 11*4(sp)
		sw		t4, 12*4(sp)
		sw		t5, 13*4(sp)
		sw		t6, 14*4(sp)
		sw		t7, 15*4(sp)
		sw		t8, 24*4(sp)
		sw		t9, 25*4(sp)
		sw		s0, 16*4(sp)
		sw		s1, 17*4(sp)
		sw		s2, 18*4(sp)
		sw		s3, 19*4(sp)
		sw		s4, 20*4(sp)
		sw		s5, 21*4(sp)
		sw		s6, 22*4(sp)
		sw		s7, 23*4(sp)
	//	sw		k0, 26*4(sp)
		sw		k1, 27*4(sp)
	//	sw		gp, 28*4(sp)
		mflo	v0
		mfhi	v1
		sw		fp, 30*4(sp)	/*	必要なし？	*/
		sw		ra, 31*4(sp)
		sw		v0, 32*4(sp)	// lo
		sw		v1, 33*4(sp)	// hi
#if 1
		swc1	$0,  38*4(sp)
		swc1	$1,  39*4(sp)
		swc1	$2,  40*4(sp)
		swc1	$3,  41*4(sp)
		swc1	$4,  42*4(sp)
		swc1	$5,  43*4(sp)
		swc1	$6,  44*4(sp)
		swc1	$7,  45*4(sp)
		swc1	$8,  46*4(sp)
		swc1	$9,  47*4(sp)
		swc1	$10, 48*4(sp)
		swc1	$11, 49*4(sp)
		swc1	$12, 50*4(sp)
		swc1	$13, 51*4(sp)
		swc1	$14, 52*4(sp)
		swc1	$15, 53*4(sp)
		swc1	$16, 54*4(sp)
		swc1	$17, 55*4(sp)
		swc1	$18, 56*4(sp)
		swc1	$19, 57*4(sp)
		swc1	$20, 58*4(sp)
		swc1	$21, 59*4(sp)
		swc1	$22, 60*4(sp)
		swc1	$23, 61*4(sp)
		swc1	$24, 62*4(sp)
		swc1	$25, 63*4(sp)
		swc1	$26, 64*4(sp)
		swc1	$27, 65*4(sp)
		swc1	$28, 66*4(sp)
		swc1	$29, 67*4(sp)
		swc1	$30, 68*4(sp)
		swc1	$31, 69*4(sp)
		cfc1	$12, $25
		sw		$12, 70*4(sp)
#else	// sp の下位3bitが 0 であるなら使える
		sdc1	$0,  38*4(sp)
		sdc1	$2,  40*4(sp)
		sdc1	$4,  42*4(sp)
		sdc1	$6,  44*4(sp)
		sdc1	$8,  46*4(sp)
		sdc1	$10, 48*4(sp)
		sdc1	$12, 50*4(sp)
		sdc1	$14, 52*4(sp)
		sdc1	$16, 54*4(sp)
		sdc1	$18, 56*4(sp)
		sdc1	$20, 58*4(sp)
		sdc1	$22, 60*4(sp)
		sdc1	$24, 62*4(sp)
		sdc1	$26, 64*4(sp)
		sdc1	$28, 66*4(sp)
		sdc1	$30, 68*4(sp)
		cfc1	$12, $25
		sw		$12, 70*4(sp)
#endif
.endm
/***************************************
 *  レジスタ復帰マクロ
 ***************************************/
.macro	popall
		.set	push
		.set	reorder
		mfc0	t0, CP0_STATUS
		.set	pop
		ori		t0, 0x1F
		xori	t0, 0x1F
		mtc0	t0, CP0_STATUS
		li		v1, 0xFF00
		and		t0, v1
		lw		v0,   4*36(sp)	// STATUS
		nor		v1, $0, v1
		and		v0, v1
		or		v0, t0
		mtc0	v0, CP0_STATUS
		lw		v1,  4*34(sp)	// EPC
		mtc0	v1, CP0_EPC

		.set	push
		.set	noat
		lw		$1,   4*1(sp)
		.set	pop

		lw		t8, 32*4(sp)	// lo
		lw		t9, 33*4(sp)	// hi
		lw		v0,  2*4(sp)
		lw		v1,  3*4(sp)
		mtlo	t8
		mthi	t9
		lw		a0,  4*4(sp)
		lw		a1,  5*4(sp)
		lw		a2,  6*4(sp)
		lw		a3,  7*4(sp)
		lw		t0,  8*4(sp)
		lw		t1,  9*4(sp)
		lw		t2, 10*4(sp)
		lw		t3, 11*4(sp)
		lw		t4, 12*4(sp)
		lw		t5, 13*4(sp)
		lw		t6, 14*4(sp)
		lw		t7, 15*4(sp)
		lw		t8, 24*4(sp)
		lw		t9, 25*4(sp)
		lw		s0, 16*4(sp)
		lw		s1, 17*4(sp)
		lw		s2, 18*4(sp)
		lw		s3, 19*4(sp)
		lw		s4, 20*4(sp)
		lw		s5, 21*4(sp)
		lw		s6, 22*4(sp)
		lw		s7, 23*4(sp)
	//	lw		k0, 26*4(sp)
		lw		k1, 27*4(sp)
	//	lw		gp, 28*4(sp)
		lw		fp, 30*4(sp)	/* 必要なし？	*/
		lw		ra, 31*4(sp)
#if 1
		lwc1	$0,  38*4(sp)
		lwc1	$1,  39*4(sp)
		lwc1	$2,  40*4(sp)
		lwc1	$3,  41*4(sp)
		lwc1	$4,  42*4(sp)
		lwc1	$5,  43*4(sp)
		lwc1	$6,  44*4(sp)
		lwc1	$7,  45*4(sp)
		lwc1	$8,  46*4(sp)
		lwc1	$9,  47*4(sp)
		lwc1	$10, 48*4(sp)
		lwc1	$11, 49*4(sp)
		lwc1	$12, 50*4(sp)
		lwc1	$13, 51*4(sp)
		lwc1	$14, 52*4(sp)
		lwc1	$15, 53*4(sp)
		lwc1	$16, 54*4(sp)
		lwc1	$17, 55*4(sp)
		lwc1	$18, 56*4(sp)
		lwc1	$19, 57*4(sp)
		lwc1	$20, 58*4(sp)
		lwc1	$21, 59*4(sp)
		lwc1	$22, 60*4(sp)
		lwc1	$23, 61*4(sp)
		lwc1	$24, 62*4(sp)
		lwc1	$25, 63*4(sp)
		lwc1	$26, 64*4(sp)
		lwc1	$27, 65*4(sp)
		lwc1	$28, 66*4(sp)
		lwc1	$29, 67*4(sp)
		lwc1	$30, 68*4(sp)
		lwc1	$31, 69*4(sp)
		lw		$12, 70*4(sp)
		ctc1	$25, $12
#else	// sp の下位3bitが 0 であるなら使える
		ldc1	$0,  38*4(sp)
		ldc1	$2,  40*4(sp)
		ldc1	$4,  42*4(sp)
		ldc1	$6,  44*4(sp)
		ldc1	$8,  46*4(sp)
		ldc1	$10, 48*4(sp)
		ldc1	$12, 50*4(sp)
		ldc1	$14, 52*4(sp)
		ldc1	$16, 54*4(sp)
		ldc1	$18, 56*4(sp)
		ldc1	$20, 58*4(sp)
		ldc1	$22, 60*4(sp)
		ldc1	$24, 62*4(sp)
		ldc1	$26, 64*4(sp)
		ldc1	$28, 66*4(sp)
		ldc1	$30, 68*4(sp)
		lw		$12, 70*4(sp)
		ctc1	$25, $12
#endif
		lw		sp, 29*4(sp)			/* スタックポインタの復帰 */
.endm
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
