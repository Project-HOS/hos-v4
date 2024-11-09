#!/usr/bin/perl
#
#	Configurator for Hyper Operating System V4
#
#
#

#	初期値
$max_semid		= 0;
$max_flgid		= 0;
$max_dtqid		= 0;
$max_mbxid		= 0;
$max_mbfid		= 0;
$max_mpfid		= 0;
$kernel_heap	= 0;
$tic_deno		= 1;
$tic_num		= 1;
$idl_stksz		= 128;
$idl_stk		= mknl_idl_stkblk;
$int_stksz		= 0;
$int_sp			= kernel_int_stk;


mainloop:
while(<>)
{
	# 空行を無視
	next mainloop if( /^\s*$/ );
	# コメント行を無視
	next mainloop if( /^#/ );

	# INCLUDE()
	if(/\s*INCLUDE\(\"\\\"(.*)\\\"\"\);\s*$/){
		push (@headerlist, $1);
	}
	elsif(/\s*INCLUDE\(\"\"(.*)\"\"\);\s*$/){
		push (@headerlist, $1);
	}
	# HOS_KERNEL_HEAP()
	elsif(/\s*HOS_KERNEL_HEAP\((.*)\);\s*$/){
		$kernel_heap = $1;
	}
	# HOS_TIM_TIC()
	elsif(/\s*HOS_TIM_TIC\((.*),(.*)\);\s*$/){
		$tic_deno = $1;
		$tic_num = $2;
	}
	# HOS_MAX_TPRI()
	elsif(/\s*HOS_MAX_TPRI\((.*)\);\s*$/){
		$max_tpri = $1;
	}
	# HOS_MIN_INTNO()
	elsif(/\s*HOS_MIN_INTNO\((.*)\);\s*$/){
		$min_intno = $1;
	}
	# HOS_MAX_INTNO()
	elsif(/\s*HOS_MAX_INTNO\((.*)\);\s*$/){
		$max_intno = $1;
	}
	# HOS_MAX_TSKID()
	elsif(/\s*HOS_MAX_TSKID\((.*)\);\s*$/){
		$max_tskid = $1;
	}
	# CRE_TSK()
	elsif (/CRE_TSK\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %tsk = ();
		$tsk{tskid} =  $1;
		$tsk{tskatr} =  $2;
		$tsk{exinf} =  $3;
		$tsk{task} =  $4;
		$tsk{itskpri} =  $5;
		$tsk{stksz} =  $6;
		$tsk{stk} =  $7;
		push (@tsklist, \%tsk);
		$tsknum++;
		$_ = $1;
		if( /\D/ ){
			$tskdef_flag = 1;
		}
	}
	# HOS_MAX_SEMID
	elsif(/\s*HOS_MAX_SEMID\((.*)\);\s*$/){
		$max_semid = $1;
	}
	# CRE_SEM()
	elsif (/CRE_SEM\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/)	{
		my %sem = ();
		$sem{semid} =  $1;
		$sem{sematr} =  $2;
		$sem{semcnt} =  $3;
		$sem{maxsem} =  $4;
		push (@semlist, \%sem);
		$semnum++;
		$_ = $1;
		if( /\D/ ){
			$semdef_flag = 1;
		}
	}
	# HOS_MAX_EXCNO
	elsif(/\s*HOS_MAX_EXCNO\((.*)\);\s*$/){
		$max_excno = $1;
	}
	# DEF_EXC()
	elsif (/DEF_EXC\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/)	{
		my %defexc = ();
		$defexc{excno} =  $1;
		$defexc{excatr} =  $2;
		$defexc{exchdr} =  $3;
		push (@defexclist, \%defexc);
		$defexcnum++;
		$_ = $1;
		if( /\D/ ){
			$defexcdef_flag = 1;
		}
	}
	# DEF_TEX()
	elsif (/DEF_TEX\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/)	{
		my %deftex = ();
		$deftex{tskid} =  $1;
		$deftex{texatr} =  $2;
		$deftex{texrtn} =  $3;
		push (@texrtnlist, \%texrtn);
		$texrtnnum++;
		$_ = $1;
		if( /\D/ ){
			$texcrtndef_flag = 1;
		}
	}
	# HOS_IDL_STK()
	elsif (/HOS_IDL_STK\(\s*(.*)\s*,\s*(.*)\s*\);/)	{
		$idl_stksz = $1;
		$idl_stk = $2;
	}
	# HOS_INT_STK
	elsif(/\s*HOS_INT_STK\((.*)\);\s*$/){
		$int_stk = $1;
	}
	# HOS_INT_SP
	elsif(/\s*HOS_INT_SP\((.*)\);\s*$/){
		$int_sp = $1;
	}
	# HOS_MAX_MBFID
	elsif(/\s*HOS_MAX_MBFID\((.*)\);\s*$/){
		$max_mbfid = $1;
	}
	# CRE_MBF()
	elsif (/CRE_MBF\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %mbf = ();
		$mbf{mbfid} =  $1;
		$mbf{mbfatr} =  $2;
		$mbf{maxmsz} =  $3;
		$mbf{mbfsz} =  $4;
		$mbf{mbf} =  $5;
		push (@mbflist, \%mbf);
		$mbfnum++;
		$_ = $1;
		if( /\D/ ){
			$mbfdef_flag = 1;
		}
	}
	# HOS_MAX_MBXID
	elsif(/\s*HOS_MAX_MBXID\((.*)\);\s*$/){
		$max_mbxid = $1;
	}
	# CRE_MBX()
	elsif (/CRE_MBX\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %mbx = ();
		$mbx{mbxid} =  $1;
		$mbx{mbxatr} =  $2;
		$mbx{mbxpri} =  $3;
		$mbx{mprihd} =  $4;
		push (@mbxlist, \%mbx);
		$mbxnum++;
		$_ = $1;
		if( /\D/ ){
			$mbxdef_flag = 1;
		}
	}
	# HOS_MAX_MPFID
	elsif(/\s*HOS_MAX_MPFID\((.*)\);\s*$/){
		$max_mpfid = $1;
	}
	# CRE_MPF()
	elsif (/CRE_MPF\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %mpf = ();
		$mpf{mpfid} =  $1;
		$mpf{mpfatr} =  $2;
		$mpf{blkcnt} =  $3;
		$mpf{blksz} =  $4;
		$mpf{mpf} =  $5;
		push (@mpflist, \%mpf);
		$mpfnum++;
		if( /\D/ ){
			$mpfdef_flag = 1;
		}
	}
	# HOS_MAX_FLGID
	elsif(/\s*HOS_MAX_FLGID\((.*)\);\s*$/){
		$max_flgid = $1;
	}
	# CRE_FLG()
	elsif (/CRE_FLG\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %flg = ();
		$flg{flgid} =  $1;
		$flg{flgatr} =  $2;
		$flg{iflgptn} =  $3;
		push (@flglist, \%flg);
		$flgnum++;
		if( /\D/ ){
			$flgdef_flag = 1;
		}
	}
	# HOS_MAX_CYCID
	elsif(/\s*HOS_MAX_CYCID\((.*)\);\s*$/){
		$max_cycid = $1;
	}
	# CRE_CYC()
	elsif (/CRE_CYC\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %cyc = ();
		$cyc{cycid} =  $1;
		$cyc{cycatr} =  $2;
		$cyc{exinf} =  $3;
		$cyc{cychdr} =  $4;
		$cyc{cyctim} =  $5;
		$cyc{cycphs} =  $6;
		push (@cyclist, \%cyc);
		$cycnum++;
		if( /\D/ ){
			$cycdef_flag = 1;
		}
	}
	# HOS_MAX_TIMOUT
	elsif(/\s*HOS_MAX_TIMOUT\((.*)\);\s*$/){
		$max_timout = $1;
	}
	# HOS_MAX_DTQID
	elsif(/\s*HOS_MAX_DTQID\((.*)\);\s*$/){
		$max_dtqid = $1;
	}
	# CRE_DTQ()
	elsif (/CRE_DTQ\(\s*(.*\S)\s*,\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %dtq = ();
		$dtq{dtqid} =  $1;
		$dtq{dtqatr} =  $2;
		$dtq{dtqcnt} =  $3;
		$dtq{dtq} =  $4;
		push (@dtqlist, \%dtq);
		$dtqnum++;
		if( /\D/ ){
			$dtqdef_flag = 1;
		}
	}
	# ATT_INI()
	elsif (/ATT_INI\(\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %attini = ();
		$attini{iniatr} =  $1;
		$attini{extinf} =  $2;
		$attini{inirtn} =  $3;
		push (@attinilist, \%attini);
		$attininum++;
		if( /\D/ ){
			$attinidef_flag = 1;
		}
	}
	# ATT_ISR()
	elsif (/ATT_ISR\(\s*\{\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*,\s*(.*\S)\s*\}\);/) {
		my %attisr = ();
		$attisr{isratr} =  $1;
		$attisr{exinf} =  $2;
		$attisr{intno} =  $3;
		$attisr{isr} =  $4;
		push (@attisrlist, \%attisr);
		$attisrnum++;
		if( /\D/ ){
			$attisrdef_flag = 1;
		}
	}
	else {
	    print "Config file syntax error : line $.\n";
	    exit(0);
	}
}

gen_cfg_c ();
gen_defid_h ();

print "done.\n";

sub gen_cfg_c
{
	open CFG, ">kernel_cfg.c" or die "Can't open kernel_cfg.c";

	print CFG "/* ------------------------------------------------------------------------ */\n";
	print CFG "/*  HOS-V4  kernel configuration                                            */\n";
	print CFG "/*    kernel object create and initialize                                   */\n";
	print CFG "/*                                                                          */\n";
	print CFG "/* ------------------------------------------------------------------------ */\n";
	print CFG "\n\n";

	print CFG "\#include \"kernel.h\"\n";
	print CFG "\#include \"kernel_id.h\"\n";
	print CFG "\n";
	foreach $ref (@headerlist) {
		print CFG "\#include \"$ref\"\n";
	}
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*                 idle stack                 */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";
	print CFG "VP         mknl_idl_stkblk[(($idl_stksz) + sizeof(VP) - 1) / sizeof(VP)];	/* idle stack block*/\n";
	print CFG "const VP   mknl_idl_stk   = (VP)($idl_stk);	/* idle stack */\n";
	print CFG "const SIZE mknl_idl_stksz = (SIZE)sizeof(mknl_idl_stkblk);	/* idle stack size */\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*           create ready queue               */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";
	print CFG "T_MKNL_QUE\tmknl_rdq_tbl[$max_tpri];\n";
	print CFG "const INT\tmknl_rdq_cnt = $max_tpri;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*                kernel heap                 */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";
	print CFG "VP kernel_heap_mem[(($kernel_heap) + sizeof(VP) - 1) / sizeof(VP)];	/* kernel heap */\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*               set time tic                 */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";
	print CFG "const UW kernel_tic_deno = TIC_DENO;\n";
	print CFG "const UW kernel_tic_div  = TIC_NUME / TIC_DENO;\n";
	print CFG "const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;\n";
	print CFG "\n\n\n";

	if( $max_timout != 0 ){
		print CFG "/* ------------------------------------------ */\n";
		print CFG "/*          create time-out queue             */\n";
		print CFG "/* ------------------------------------------ */\n";
		print CFG "\n";
		print CFG "T_MKNL_TIMOUT mknl_timout[$max_timout];\n";
		print CFG "const INT     mknl_timout_size = $max_timout;\n";
		print CFG "\n\n\n";
	}

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*          create task objects               */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";
	print CFG "/* stack area */\n";
	$i = 1;
	foreach $ref (@tsklist) {
		print CFG "static VP kernel_tsk$i\_stk[(($$ref{stksz}) + sizeof(VP) - 1) / sizeof(VP)];\n";
		$i++;
	}
	print CFG "\n";

	print CFG "/* task control block for rom area */\n";
	print CFG "const T_KERNEL_TCB_ROM kernel_tcb_rom[$tsknum] =\n";
	print CFG "\t{\n";
	$i = 1;
	foreach $ref (@tsklist) {
		print CFG "\t\t{(ATR)($$ref{tskatr}), (VP_INT)($$ref{exinf}), (FP)($$ref{task}), (PRI)($$ref{itskpri}), (SIZE)($$ref{stksz}), (VP)kernel_tsk$i\_stk},\n";
		$i++;
	}
	print CFG "\t};\n\n";

	if( $max_tskid < $tsknum ){
		$max_tskid = $tsknum;
	}

	print CFG "/* task control block for ram area */\n";
	print CFG "T_KERNEL_TCB_RAM kernel_tcb_ram[$tsknum];\n\n";
	print CFG "/* task control block table */\n";
	print CFG "T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[$max_tskid] =\n";
	print CFG "\t{\n";
	$i = 0;
	while($i < $max_tskid ){
		if( $i < $tsknum ){
			print CFG "\t\t&kernel_tcb_ram[$i],\n";
		}
		else{
			print CFG "\t\tNULL,\n";
		}
		$i++;
	}
	print CFG "\t};\n\n";

	print CFG "/* task control block count */\n";
	print CFG "const INT kernel_tcb_cnt = $max_tskid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*         create semaphore objects           */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_semid < $semnum ){
		$max_semid = $semnum;
	}

	if( $max_semid != 0 ){
		print CFG "/* semaphore control block for rom area */\n";
		print CFG "const T_KERNEL_SEMCB_ROM kernel_semcb_rom[$semnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@semlist) {
			print CFG "\t\t{(ATR)($$ref{sematr}), (UINT)($$ref{semcnt}), (UINT)($$ref{maxsem})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* semaphore control block for ram area */\n";
		print CFG "T_KERNEL_SEMCB_RAM kernel_semcb_ram[$semnum];\n\n";

		print CFG "/* semaphore control block table */\n";
		print CFG "T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[$max_semid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_semid ){
			if( $i < $semnum ){
				print CFG "\t\t&kernel_semcb_ram[$i],\n";
			}
			else{
				print CFG "\t\tNULL,\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* semaphore control block count */\n";
	print CFG "const INT kernel_semcb_cnt = $max_semid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*        create event flag objects           */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_flgid < $flgnum ){
		$max_flgid = $flgnum;
	}

	if( $max_flgid != 0 ){
		print CFG "/* event flag control block for rom area */\n";
		print CFG "const T_KERNEL_FLGCB_ROM kernel_flgcb_rom[$flgnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@flglist) {
			print CFG "\t\t{(ATR)($$ref{flgatr}), (FLGPTN)($$ref{iflgptn})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* event flag control block for ram area */\n";
		print CFG "T_KERNEL_FLGCB_RAM kernel_flgcb_ram[$flgnum];\n\n";

		print CFG "/* event flag control block table */\n";
		print CFG "T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[$max_flgid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_flgid ){
			if( $i < $flgnum ){
				print CFG "\t\t&kernel_flgcb_ram[$i],\n";
			}
			else{
				print CFG "\t};\n\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* event flag control block count */\n";
	print CFG "const INT kernel_flgcb_cnt = $max_flgid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*        create data queue objects           */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_dtqid < $dtqnum ){
		$max_dtqid = $dtqnum;
	}

	if( $max_dtqid != 0 ){
		print CFG "/* data queue control block for rom area */\n";
		print CFG "const T_KERNEL_DTQCB_ROM kernel_dtqcb_rom[$dtqnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@dtqlist) {
			print CFG "\t\t{(ATR)($$ref{dtqatr}), (FLGPTN)($$ref{dtqcnt}), (VP_INT *)($$ref{dtq})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* data queue control block for ram area */\n";
		print CFG "T_KERNEL_DTQCB_RAM kernel_dtqcb_ram[$dtqnum];\n\n";

		print CFG "/* data queue control block table */\n";
		print CFG "T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[$max_dtqid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_dtqid ){
			if( $i < $dtqnum ){
				print CFG "\t\t&kernel_dtqcb_ram[$i],\n";
			}
			else{
				print CFG "\t};\n\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* data queue control block count */\n";
	print CFG "const INT kernel_dtqcb_cnt = $max_dtqid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*         create mail box objects            */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_mbxid < $mbxnum ){
		$max_mbxid = $mbxnum;
	}

	if( $max_mbxid != 0 ){
		print CFG "/* mail box control block for rom area */\n";
		print CFG "const T_KERNEL_MBXCB_ROM kernel_mbxcb_rom[$mbxnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@mbxlist) {
			print CFG "\t\t{(ATR)($$ref{mbxatr}), (PRI)($$ref{mbxpri}), (VP)($$ref{mprihd})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* mail box control block for ram area */\n";
		print CFG "T_KERNEL_MBXCB_RAM kernel_mbxcb_ram[$mbxnum];\n\n";

		print CFG "/* mail box control block table */\n";
		print CFG "T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[$max_mbxid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_mbxid ){
			if( $i < $mbxnum ){
				print CFG "\t\t&kernel_mbxcb_ram[$i],\n";
			}
			else{
				print CFG "\t};\n\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* mail box control block count */\n";
	print CFG "const INT kernel_mbxcb_cnt = $max_mbxid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*      create message buffer objects         */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_mbfid < $mbfnum ){
		$max_mbfid = $mbfnum;
	}

	if( $max_mbfid != 0 ){
		print CFG "/* message buffer control block for rom area */\n";
		print CFG "const T_KERNEL_MBFCB_ROM kernel_mbfcb_rom[$mbfnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@mbflist) {
			print CFG "\t\t{(ATR)($$ref{mbfatr}), (UINT)($$ref{maxmsz}), (SIZE)($$ref{mbfsz}),(VP)($$ref{mbf})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* message buffer control block for ram area */\n";
		print CFG "T_KERNEL_MBFCB_RAM kernel_mbfcb_ram[$mbfnum];\n\n";

		print CFG "/* message buffer control block table */\n";
		print CFG "T_KERNEL_MBFCB_RAM *kernel_mbfcb_ram_tbl[$max_mbfid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_mbfid ){
			if( $i < $mbfnum ){
				print CFG "\t\t&kernel_mbfcb_ram[$i],\n";
			}
			else{
				print CFG "\t};\n\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* mail box control block count */\n";
	print CFG "const INT kernel_mbfcb_cnt = $max_mbfid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*   create fixed size memory-pool objects    */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $max_mpfid < $mpfnum ){
		$max_mpfid = $mpfnum;
	}

	if( $max_mpfid != 0 ){
		print CFG "/* fixed size memory-pool control block for rom area */\n";
		print CFG "const T_KERNEL_MPFCB_ROM kernel_mpfcb_rom[$mpfnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@mpflist) {
			print CFG "\t\t{(ATR)($$ref{mpfatr}), (UINT)($$ref{blkcnt}), (SIZE)($$ref{blksz}), (VP)($$ref{mpf})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* fixed size memory-pool control block for ram area */\n";
		print CFG "T_KERNEL_MPFCB_RAM kernel_mpfcb_ram[$mpfnum];\n\n";

		print CFG "/* fixed size memory-pool control block table */\n";
		print CFG "T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[$max_mpfid] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $max_mpfid ){
			if( $i < $mpfnum ){
				print CFG "\t\t&kernel_mpfcb_ram[$i],\n";
			}
			else{
				print CFG "\t};\n\n";
			}
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* fixed size memory-pool control block count */\n";
	print CFG "const INT kernel_mpfcb_cnt = $max_mpfid;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*       create cyclic handler objects        */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $cycnum != 0 ){
		print CFG "/* cyclic handler control block for rom area */\n";
		print CFG "const T_KERNEL_CYCCB_ROM kernel_cyccb_rom[$cycnum] =\n";
		print CFG "\t{\n";
		foreach $ref (@cyclist) {
			print CFG "\t\t{(ATR)($$ref{cycatr}), (VP_INT)($$ref{exinf}), (FP)($$ref{cychdr}), (RELTIM)($$ref{cyctim})},\n";
		}
		print CFG "\t};\n\n";

		print CFG "/* cyclic handler control block for ram area */\n";
		print CFG "T_KERNEL_CYCCB_RAM kernel_cyccb_ram[$cycnum];\n\n";

		print CFG "/* cyclic handler control block table */\n";
		print CFG "T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[$mbfnum] =\n";
		print CFG "\t{\n";
		$i = 0;
		while($i < $cycnum ){
			print CFG "\t\t&kernel_cyccb_ram[$i],\n";
			$i++;
		}
		print CFG "\t};\n\n";
	}

	print CFG "/* cyclic handler control block count */\n";
	print CFG "const INT kernel_cyccb_cnt = $cycnum;\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*        interrupt control objects           */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	if( $int_stksz != 0 ){
		print CFG "/* interrupt stack */\n";
		print CFG "VP       kernel_int_stk[($int_stksz + sizeof(VP) - 1) / sizeof(VP)];\n";
		print CFG "const VP kernel_int_sp = &$int_sp[($int_stksz + sizeof(VP) - 1) / sizeof(VP)];\n";
		print CFG "\n";
	}

	print CFG "/* interrupt control */\n";
	$intcnt = $max_intno - $min_intno + 1;
	print CFG "T_KERNEL_INTCB kernel_intcb_tbl[$intcnt];		/* interrupt control block table */\n";
	print CFG "const INT      kernel_intcb_cnt = $intcnt;		/* interrupt control block count */\n";
	print CFG "const INTNO    kernel_min_intno = $min_intno;		/* minimum intrrupt number */\n";
	print CFG "\n";

	print CFG "/* interrupt service routine control */\n";
	print CFG "const INT      kernel_isrcb_cnt = 0;		/* ISR control block count */\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*    CPU exception handler control objects   */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	print CFG "/* interrupt control */\n";
	print CFG "T_KERNEL_EXCCB kernel_exccb_tbl[1];		/* CPU exception handler control block table */\n";
	print CFG "const INT      kernel_exccb_cnt = 1;		/* CPU exception handler control block count */\n";
	print CFG "const EXCNO    kernel_min_excno = 0;		/* minimum CPU exception handler number */\n";
	print CFG "\n\n\n";

	print CFG "/* ------------------------------------------ */\n";
	print CFG "/*          initialize functions              */\n";
	print CFG "/* ------------------------------------------ */\n";
	print CFG "\n";

	print CFG "/* object initialize */\n";
	print CFG "void kernel_cfg_init(void)\n";
	print CFG "{\n";
	print CFG "\tint i;\n";

	if( $tsknum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize task control block */\n";
		print CFG "\tfor ( i = 0; i < 5; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_tcb_ram[i].tcb_rom = &kernel_tcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $semnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize semaphore control block */\n";
		print CFG "\tfor ( i = 0; i < $semnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_semcb_ram[i].semcb_rom = &kernel_semcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $flgnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize event flag control block */\n";
		print CFG "\tfor ( i = 0; i < $flgnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_flgcb_ram[i].flgcb_rom = &kernel_flgcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $dtqnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize data queue control block */\n";
		print CFG "\tfor ( i = 0; i < $dtqnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_dtqcb_ram[i].dtqcb_rom = &kernel_dtqcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $mbxnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize mail box control block */\n";
		print CFG "\tfor ( i = 0; i < $mbxnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_mbxcb_ram[i].mbxcb_rom = &kernel_mbxcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $mbfnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize message buffer control block */\n";
		print CFG "\tfor ( i = 0; i < $mbfnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_mbfcb_ram[i].mbfcb_rom = &kernel_mbfcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $mpfnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize fixed size memory-pool control block */\n";
		print CFG "\tfor ( i = 0; i < $mpfnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_mpfcb_ram[i].mpfcb_rom = &kernel_mpfcb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $cycnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize cyclic handler control block */\n";
		print CFG "\tfor ( i = 0; i < $cycnum; i++ )\n";
		print CFG "\t{\n";
		print CFG "\t\tkernel_cyccb_ram[i].cyccb_rom = &kernel_cyccb_rom[i];\n";
		print CFG "\t}\n";
	}

	if( $attisrnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize interrupt table */\n";
		foreach $ref (@attisrlist) {
			print CFG "\tkernel_intcb_tbl[$$ref{intno}].exinf = (VP_INT)($$ref{exinf});\n";
			print CFG "\tkernel_intcb_tbl[$$ref{intno}].isr   = (FP)($$ref{isr});\n";
		}
	}

	if( $defexcnum != 0 ){
		print CFG "\t\n";
		print CFG "\t\n";
		print CFG "\t/* initialize CPU exception handler table */\n";
		foreach $ref (@defexclist) {
			print CFG "\tkernel_exccb_tbl[$$ref{excno}].exchdr = (FP)($$ref{exchdr});\n";
		}
	}

	print CFG "}\n";
	print CFG "\n";
	print CFG "/* start up */\n";
	print CFG "void kernel_cfg_start(void)\n";
	print CFG "{\n";
	print CFG "\tkernel_ini_mem(kernel_heap_mem, sizeof(kernel_heap_mem));\t\t/* initialize kernel heap */\n";
	print CFG "\n";

	if( $tsknum != 0 ){
		print CFG "\tkernel_ini_tsk();\t\t/* initialize task */\n";
	}

	if( $semnum != 0 ){
		print CFG "\tkernel_ini_sem();\t\t/* initialize semaphore */\n";
	}

	if( $dtqnum != 0 ){
		print CFG "\tkernel_ini_dtq();		/* initialize data queue */\n";
	}

	if( $mbxnum != 0 ){
		print CFG "\tkernel_ini_mbx();		/* initialize mail box */\n";
	}

	if( $mbfnum != 0 ){
		print CFG "\tkernel_ini_mbf();		/* initialize message buffer */\n";
	}

	if( $mpfnum != 0 ){
		print CFG "\tkernel_ini_mpf();		/* initialize fixed size memory-pool */\n";
	}

	if( $cycnum != 0 ){
		print CFG "\tkernel_ini_cyc();		/* initialize cyclic handler */\n";
	}

	if( $flgnum != 0 ){
		print CFG "\tkernel_ini_flg();\t\t/* initialize event flag */\n";
	}

	print CFG "\n";

	if( $attininum != 0 ){
		print CFG "\t/* call initialize routine*/\n";
		foreach $ref (@attinilist) {
			print CFG "\t((FP)($$ref{inirtn}))((VP_INT)($$ref{extinf}));\n";
		}
	}

	print CFG "}\n";
	print CFG "\n\n";
	print CFG "/* ------------------------------------------------------------------------ */\n";
	print CFG "/*  End of file                                                             */\n";
	print CFG "/* ------------------------------------------------------------------------ */\n";
}

sub gen_defid_h
{
	open FH, ">kernel_id.h" or die "Can't open kernel_id.h";

	print FH "/* ------------------------------------------------------------------------ */\n";
	print FH "/*  HOS-V4  kernel configuration                                            */\n";
	print FH "/*    kernel object ID definition                                           */\n";
	print FH "/*                                                                          */\n";
	print FH "/* ------------------------------------------------------------------------ */\n";
	print FH "\n\n";

	print FH "#ifndef __HOS_V4__kernel_cfg_h__\n";
	print FH "#define __HOS_V4__kernel_cfg_h__\n";
	print FH "\n\n\n";

	print FH "/* time tic */\n";
	print FH "#define TIC_NUME\t\t$tic_deno\n";
	print FH "#define TIC_DENO\t\t$tic_num\n";

	if( $tskdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* task ID definetion */\n";
		$i = 1;
		foreach $ref (@tsklist) {
			$_ = $$ref{tskid};
			if( /\D/ ){
				print FH "\#define $$ref{tskid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $semdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* semaphore ID definetion */\n";
		$i = 1;
		foreach $ref (@semlist) {
			$_ = $$ref{semid};
			if( /\D/ ){
				print FH "\#define $$ref{semid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $flgdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* event flag ID definetion */\n";
		$i = 1;
		foreach $ref (@flglist) {
			$_ = $$ref{flgid};
			if( /\D/ ){
				print FH "\#define $$ref{flgid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $dtqdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* data queue ID definetion */\n";
		$i = 1;
		foreach $ref (@dtqlist) {
			$_ = $$ref{dtqid};
			if( /\D/ ){
				print FH "\#define $$ref{dtqid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $mbxdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* mail box ID definetion */\n";
		$i = 1;
		foreach $ref (@mbxlist) {
			$_ = $$ref{mbxid};
			if( /\D/ ){
				print FH "\#define $$ref{mbxid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $mbfdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* message buffer ID definetion */\n";
		$i = 1;
		foreach $ref (@mbflist) {
			$_ = $$ref{mbfid};
			if( /\D/ ){
				print FH "\#define $$ref{mbfid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $mpfdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* fixed size memory-pool ID definetion */\n";
		$i = 1;
		foreach $ref (@mpflist) {
			$_ = $$ref{mpfid};
			if( /\D/ ){
				print FH "\#define $$ref{mpfid}\t\t$i\n";
			}
			$i++;
		}
	}

	if( $cycdef_flag == 1 ){
		print FH "\n\n";
		print FH "/* cyclic handler ID definetion */\n";
		$i = 1;
		foreach $ref (@cyclist) {
			$_ = $$ref{cycid};
			if( /\D/ ){
				print FH "\#define $$ref{cycid}\t\t$i\n";
			}
			$i++;
		}
	}

	print FH "\n\n\n";
	print FH "#endif	/* __HOS_V4__kernel_cfg_h__ */\n";
	print FH "\n\n";

	print FH "/* ------------------------------------------------------------------------ */\n";
	print FH "/*  End of file                                                             */\n";
	print FH "/* ------------------------------------------------------------------------ */\n";
}
