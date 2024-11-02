# ---------------------------------------------------------------------------
#	Hyper Operating System V4  μITRON4.0仕様 Real-Time OS
#		ライブラリメイクファイル 78K0Rコア用
#
#		コンパイルには NEC Electronics 提供の 78K0R開発環境を利用します。
#		78K0R開発環境のあるディレクトリを TOOLDIR1,2 にて定義してください。
#
#									Copyright (C) 1998-2009 by Project HOS
#									http://sourceforge.jp/projects/hos/
# ---------------------------------------------------------------------------

TOOLDIR1= "C:\Program Files\NEC Electronics Tools\RA78K0R\W1.31"
TOOLDIR2= "C:\Program Files\NEC Electronics Tools\CC78K0R\W2.10"

# パス定義
HOSROOT    = ../../..
INCDIR     = $(HOSROOT)/include
SRCDIR     = $(HOSROOT)/src
PACDIR     = $(SRCDIR)/78k0r
PACASMDIR  = $(PACDIR)/cc78k0r
MKNLDIR    = $(SRCDIR)/mknl
MKNLSYSDIR = $(MKNLDIR)/sys
MKNLTSKDIR = $(MKNLDIR)/tsk
MKNLQUEDIR = $(MKNLDIR)/que
MKNLTMODIR = $(MKNLDIR)/tmout
KERNELDIR  = $(SRCDIR)/kernel
KNLHOSDIR  = $(KERNELDIR)/hos
KNLMEMDIR  = $(KERNELDIR)/mem
KNLHEPDIR  = $(KERNELDIR)/hep
KNLTSKDIR  = $(KERNELDIR)/tsk
KNLSEMDIR  = $(KERNELDIR)/sem
KNLFLGDIR  = $(KERNELDIR)/flg
KNLDTQDIR  = $(KERNELDIR)/dtq
KNLMBXDIR  = $(KERNELDIR)/mbx
KNLMBFDIR  = $(KERNELDIR)/mbf
KNLMPFDIR  = $(KERNELDIR)/mpf
KNLTIMDIR  = $(KERNELDIR)/tim
KNLCYCDIR  = $(KERNELDIR)/cyc
KNLALMDIR  = $(KERNELDIR)/alm
KNLSYSDIR  = $(KERNELDIR)/sys
KNLINTDIR  = $(KERNELDIR)/int


# ツール
CC     = $(TOOLDIR2)/bin/cc78k0r
ASM    = $(TOOLDIR1)/bin/ra78k0r
LIBR   = $(TOOLDIR1)/bin/lb78k0r

# オプション
CFLAGS = -cF1166A0 -i$(INCDIR) -_msgoff -rd4s4 -qx3 -zp -a \
			-y"c:\program files\nec electronics tools\dev" # -d__USE_RB__
AFLAGS = -cf1166a0 -i$(INCDIR) -i$(PACASMDIR) -_msgoff -np # -d__USE_RB__

# ターゲット
LIB    = libh478k0r.lib

all:	$(LIB)

#インクルードファイル
INCS = $(INCDIR)/itron.h \
       $(INCDIR)/hoserchk.h \
       $(INCDIR)/hosdenv.h \
       $(INCDIR)/mknl.h \
       $(INCDIR)/kernel.h \
       $(INCDIR)/knl_hos.h \
       $(INCDIR)/knl_hep.h \
       $(INCDIR)/knl_mem.h \
       $(INCDIR)/knl_tsk.h \
       $(INCDIR)/knl_sem.h \
       $(INCDIR)/knl_flg.h \
       $(INCDIR)/knl_dtq.h \
       $(INCDIR)/knl_mbx.h \
       $(INCDIR)/knl_mpf.h \
       $(INCDIR)/knl_mbf.h \
       $(INCDIR)/knl_tim.h \
       $(INCDIR)/knl_sys.h \
       $(INCDIR)/knl_int.h \
       $(INCDIR)/knl_exc.h \
       $(INCDIR)/sh/hospac.h


# オブジェクトファイル
OBJS = mini_sys.rel mexe_sys.rel midl_lop.rel msta_stu.rel mext_stu.rel \
       msta_tsk.rel mter_tsk.rel mchg_pri.rel mrot_rdq.rel \
       mwai_tsk.rel mwup_tsk.rel msus_tsk.rel mrsm_tsk.rel \
       mexe_dsp.rel mdly_dsp.rel msrh_top.rel \
       mras_tex.rel mexe_tex.rel \
       madd_que.rel madf_que.rel madp_que.rel mrmv_que.rel \
       mrot_que.rel mclr_que.rel \
       mtic_tmo.rel madd_tmo.rel mrmv_tmo.rel \
       sta_hos.rel ini_mem.rel alc_mem.rel fre_mem.rel \
       cre_hep.rel alc_hep.rel fre_hep.rel \
       ini_tsk.rel cre_tsk.rel acre_tsk.rel kcre_tsk.rel del_tsk.rel \
       act_tsk.rel can_act.rel sta_tsk.rel ext_tsk.rel exd_tsk.rel \
       ter_tsk.rel chg_pri.rel get_pri.rel ref_tst.rel \
       slp_tsk.rel tslp_tsk.rel wup_tsk.rel can_wup.rel rel_wai.rel \
       sus_tsk.rel rsm_tsk.rel frsm_tsk.rel dly_tsk.rel \
       ras_tex.rel ktex_ent.rel dis_tex.rel ena_tex.rel sns_tex.rel \
       ini_sem.rel cre_sem.rel acre_sem.rel kcre_sem.rel del_sem.rel \
       sig_sem.rel wai_sem.rel pol_sem.rel twai_sem.rel ref_sem.rel \
       ini_flg.rel cre_flg.rel acre_flg.rel kcre_flg.rel del_flg.rel \
       set_flg.rel clr_flg.rel wai_flg.rel pol_flg.rel \
       twai_flg.rel chk_flg.rel ref_flg.rel \
       cre_dtq.rel acre_dtq.rel kcre_dtq.rel del_dtq.rel \
       snd_dtq.rel psnd_dtq.rel tsnd_dtq.rel fsnd_dtq.rel \
       rcv_dtq.rel prcv_dtq.rel trcv_dtq.rel ref_dtq.rel \
       cre_mbx.rel acre_mbx.rel kcre_mbx.rel del_mbx.rel \
       snd_mbx.rel rcv_mbx.rel prcv_mbx.rel trcv_mbx.rel ref_mbx.rel \
       ini_mbf.rel cre_mbf.rel acre_mbf.rel kcre_mbf.rel del_mbf.rel \
       snd_mbf.rel psnd_mbf.rel tsnd_mbf.rel ksnd_mbf.rel \
       rcv_mbf.rel prcv_mbf.rel trcv_mbf.rel krcv_mbf.rel ref_mbf.rel \
       ini_mpf.rel cre_mpf.rel acre_mpf.rel kcre_mpf.rel del_mpf.rel \
       get_mpf.rel pget_mpf.rel tget_mpf.rel rel_mpf.rel ref_mpf.rel \
       ini_tim.rel isig_tim.rel set_tim.rel get_tim.rel \
       add_tml.rel rmv_tml.rel \
       ini_cyc.rel cyc_hdr.rel sta_cyc.rel stp_cyc.rel \
       cre_cyc.rel acre_cyc.rel kcre_cyc.rel del_cyc.rel \
       ini_alm.rel alm_hdr.rel sta_alm.rel stp_alm.rel \
       ram_int.rel exe_int.rel \
       get_tid.rel kget_tid.rel rot_rdq.rel \
       loc_cpu.rel unl_cpu.rel dis_dsp.rel ena_dsp.rel \
       sns_ctx.rel sns_loc.rel sns_dsp.rel sns_dpn.rel \
       ref_ver.rel

# ライブラリ生成
$(LIB): pacctx.rel pacint.rel $(OBJS) libh478k0r.slb
	$(LIBR) < libh478k0r.slb

# プロセッサ依存
pacctx.rel: $(PACASMDIR)/pacctx.asm $(PACASMDIR)/78k0rregs.inc
	$(ASM) $(AFLAGS) -o$@ $(PACASMDIR)/pacctx.asm

pacint.rel: $(PACASMDIR)/pacint.asm $(PACASMDIR)/78k0rregs.inc
	$(ASM) $(AFLAGS) -o$@ $(PACASMDIR)/pacint.asm

pacimsk.rel: $(PACDIR)/pacimsk.c
	$(CC) $(CFLAGS) -no -a_tmp.asm $(PACDIR)/pacimsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

hospac.rel: $(PACDIR)/hospac.c
	$(CC) $(CFLAGS) -no -a_tmp.asm $(PACDIR)/hospac.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# μカーネル システム制御
mini_sys.rel: $(MKNLSYSDIR)/mini_sys.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLSYSDIR)/mini_sys.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mexe_sys.rel: $(MKNLSYSDIR)/mexe_sys.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLSYSDIR)/mexe_sys.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

midl_lop.rel: $(MKNLSYSDIR)/midl_lop.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLSYSDIR)/midl_lop.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

msta_stu.rel: $(MKNLSYSDIR)/msta_stu.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLSYSDIR)/msta_stu.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mext_stu.rel: $(MKNLSYSDIR)/mext_stu.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLSYSDIR)/mext_stu.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# μカーネル タスク制御
msta_tsk.rel: $(MKNLTSKDIR)/msta_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/msta_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mter_tsk.rel: $(MKNLTSKDIR)/mter_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mter_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mchg_pri.rel: $(MKNLTSKDIR)/mchg_pri.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mchg_pri.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mrot_rdq.rel: $(MKNLTSKDIR)/mrot_rdq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mrot_rdq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mwai_tsk.rel: $(MKNLTSKDIR)/mwai_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mwai_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mwup_tsk.rel: $(MKNLTSKDIR)/mwup_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mwup_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

msus_tsk.rel: $(MKNLTSKDIR)/msus_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/msus_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mrsm_tsk.rel: $(MKNLTSKDIR)/mrsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mrsm_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mexe_dsp.rel: $(MKNLTSKDIR)/mexe_dsp.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mexe_dsp.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mdly_dsp.rel: $(MKNLTSKDIR)/mdly_dsp.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mdly_dsp.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

msrh_top.rel: $(MKNLTSKDIR)/msrh_top.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/msrh_top.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mras_tex.rel: $(MKNLTSKDIR)/mras_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mras_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mexe_tex.rel: $(MKNLTSKDIR)/mexe_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTSKDIR)/mexe_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# μカーネル タスクキュー管理
madd_que.rel: $(MKNLQUEDIR)/madd_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/madd_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

madf_que.rel: $(MKNLQUEDIR)/madf_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/madf_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

madp_que.rel: $(MKNLQUEDIR)/madp_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/madp_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mrmv_que.rel: $(MKNLQUEDIR)/mrmv_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/mrmv_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mrot_que.rel: $(MKNLQUEDIR)/mrot_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/mrot_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mclr_que.rel: $(MKNLQUEDIR)/mclr_que.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLQUEDIR)/mclr_que.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# μカーネル タイムアウトキュー管理
mtic_tmo.rel: $(MKNLTMODIR)/mtic_tmo.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTMODIR)/mtic_tmo.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

madd_tmo.rel: $(MKNLTMODIR)/madd_tmo.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTMODIR)/madd_tmo.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

mrmv_tmo.rel: $(MKNLTMODIR)/mrmv_tmo.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(MKNLTMODIR)/mrmv_tmo.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# カーネル固有
sta_hos.rel: $(KNLHOSDIR)/sta_hos.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLHOSDIR)/sta_hos.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# ヒープメモリ
cre_hep.rel: $(KNLHEPDIR)/cre_hep.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLHEPDIR)/cre_hep.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

alc_hep.rel: $(KNLHEPDIR)/alc_hep.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLHEPDIR)/alc_hep.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

fre_hep.rel: $(KNLHEPDIR)/fre_hep.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLHEPDIR)/fre_hep.c 
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# カーネルメモリ管理
ini_mem.rel: $(KNLMEMDIR)/ini_mem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMEMDIR)/ini_mem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

alc_mem.rel: $(KNLMEMDIR)/alc_mem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMEMDIR)/alc_mem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

fre_mem.rel: $(KNLMEMDIR)/fre_mem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMEMDIR)/fre_mem.c 
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# タスク
ini_tsk.rel: $(KNLTSKDIR)/ini_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ini_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_tsk.rel: $(KNLTSKDIR)/cre_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/cre_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_tsk.rel: $(KNLTSKDIR)/acre_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/acre_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_tsk.rel: $(KNLTSKDIR)/kcre_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/kcre_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_tsk.rel: $(KNLTSKDIR)/del_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/del_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

act_tsk.rel: $(KNLTSKDIR)/act_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/act_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

can_act.rel: $(KNLTSKDIR)/can_act.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/can_act.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sta_tsk.rel: $(KNLTSKDIR)/sta_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/sta_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ext_tsk.rel: $(KNLTSKDIR)/ext_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ext_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

exd_tsk.rel: $(KNLTSKDIR)/exd_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/exd_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ter_tsk.rel: $(KNLTSKDIR)/ter_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ter_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

chg_pri.rel: $(KNLTSKDIR)/chg_pri.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/chg_pri.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

get_pri.rel: $(KNLTSKDIR)/get_pri.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/get_pri.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_tst.rel: $(KNLTSKDIR)/ref_tst.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ref_tst.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

slp_tsk.rel: $(KNLTSKDIR)/slp_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/slp_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

tslp_tsk.rel: $(KNLTSKDIR)/tslp_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/tslp_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

wup_tsk.rel: $(KNLTSKDIR)/wup_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/wup_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

can_wup.rel: $(KNLTSKDIR)/can_wup.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/can_wup.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rel_wai.rel: $(KNLTSKDIR)/rel_wai.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/rel_wai.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sus_tsk.rel: $(KNLTSKDIR)/sus_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/sus_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rsm_tsk.rel: $(KNLTSKDIR)/rsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/rsm_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

frsm_tsk.rel: $(KNLTSKDIR)/frsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/frsm_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

dly_tsk.rel: $(KNLTSKDIR)/dly_tsk.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/dly_tsk.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ktex_ent.rel: $(KNLTSKDIR)/ktex_ent.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ktex_ent.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ras_tex.rel: $(KNLTSKDIR)/ras_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ras_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

dis_tex.rel: $(KNLTSKDIR)/dis_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/dis_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ena_tex.rel: $(KNLTSKDIR)/ena_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/ena_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sns_tex.rel: $(KNLTSKDIR)/sns_tex.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTSKDIR)/sns_tex.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# セマフォ
ini_sem.rel: $(KNLSEMDIR)/ini_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/ini_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_sem.rel: $(KNLSEMDIR)/cre_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/cre_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_sem.rel: $(KNLSEMDIR)/acre_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/acre_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_sem.rel: $(KNLSEMDIR)/kcre_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/kcre_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_sem.rel: $(KNLSEMDIR)/del_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/del_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sig_sem.rel: $(KNLSEMDIR)/sig_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/sig_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

wai_sem.rel: $(KNLSEMDIR)/wai_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/wai_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

pol_sem.rel: $(KNLSEMDIR)/pol_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/pol_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

twai_sem.rel: $(KNLSEMDIR)/twai_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/twai_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_sem.rel: $(KNLSEMDIR)/ref_sem.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSEMDIR)/ref_sem.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# イベントフラグ
ini_flg.rel: $(KNLFLGDIR)/ini_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/ini_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_flg.rel: $(KNLFLGDIR)/cre_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/cre_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_flg.rel: $(KNLFLGDIR)/acre_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/acre_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_flg.rel: $(KNLFLGDIR)/kcre_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/kcre_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_flg.rel: $(KNLFLGDIR)/del_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/del_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

set_flg.rel: $(KNLFLGDIR)/set_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/set_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

clr_flg.rel: $(KNLFLGDIR)/clr_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/clr_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

wai_flg.rel: $(KNLFLGDIR)/wai_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/wai_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

pol_flg.rel: $(KNLFLGDIR)/pol_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/pol_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

twai_flg.rel: $(KNLFLGDIR)/twai_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/twai_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

chk_flg.rel: $(KNLFLGDIR)/chk_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/chk_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_flg.rel: $(KNLFLGDIR)/ref_flg.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLFLGDIR)/ref_flg.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# データキュー
cre_dtq.rel: $(KNLDTQDIR)/cre_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/cre_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_dtq.rel: $(KNLDTQDIR)/acre_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/acre_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_dtq.rel: $(KNLDTQDIR)/kcre_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/kcre_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_dtq.rel: $(KNLDTQDIR)/del_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/del_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

snd_dtq.rel: $(KNLDTQDIR)/snd_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/snd_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

psnd_dtq.rel: $(KNLDTQDIR)/psnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/psnd_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

tsnd_dtq.rel: $(KNLDTQDIR)/tsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/tsnd_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

fsnd_dtq.rel: $(KNLDTQDIR)/fsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/fsnd_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rcv_dtq.rel: $(KNLDTQDIR)/rcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/rcv_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

prcv_dtq.rel: $(KNLDTQDIR)/prcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/prcv_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

trcv_dtq.rel: $(KNLDTQDIR)/trcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/trcv_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_dtq.rel: $(KNLDTQDIR)/ref_dtq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLDTQDIR)/ref_dtq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# メールボックス
cre_mbx.rel: $(KNLMBXDIR)/cre_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/cre_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_mbx.rel: $(KNLMBXDIR)/acre_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/acre_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_mbx.rel: $(KNLMBXDIR)/kcre_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/kcre_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_mbx.rel: $(KNLMBXDIR)/del_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/del_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

snd_mbx.rel: $(KNLMBXDIR)/snd_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/snd_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rcv_mbx.rel: $(KNLMBXDIR)/rcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/rcv_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

prcv_mbx.rel: $(KNLMBXDIR)/prcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/prcv_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

trcv_mbx.rel: $(KNLMBXDIR)/trcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/trcv_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_mbx.rel: $(KNLMBXDIR)/ref_mbx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBXDIR)/ref_mbx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# メッセージバッファ
ini_mbf.rel: $(KNLMBFDIR)/ini_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/ini_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_mbf.rel: $(KNLMBFDIR)/cre_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/cre_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_mbf.rel: $(KNLMBFDIR)/acre_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/acre_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_mbf.rel: $(KNLMBFDIR)/kcre_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/kcre_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_mbf.rel: $(KNLMBFDIR)/del_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/del_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

snd_mbf.rel: $(KNLMBFDIR)/snd_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/snd_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

psnd_mbf.rel: $(KNLMBFDIR)/psnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/psnd_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

tsnd_mbf.rel: $(KNLMBFDIR)/tsnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/tsnd_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ksnd_mbf.rel: $(KNLMBFDIR)/ksnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/ksnd_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rcv_mbf.rel: $(KNLMBFDIR)/rcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/rcv_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

prcv_mbf.rel: $(KNLMBFDIR)/prcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/prcv_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

trcv_mbf.rel: $(KNLMBFDIR)/trcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/trcv_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

krcv_mbf.rel: $(KNLMBFDIR)/krcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/krcv_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_mbf.rel: $(KNLMBFDIR)/ref_mbf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMBFDIR)/ref_mbf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# 固定長メモリプール
ini_mpf.rel: $(KNLMPFDIR)/ini_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/ini_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_mpf.rel: $(KNLMPFDIR)/cre_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/cre_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_mpf.rel: $(KNLMPFDIR)/acre_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/acre_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_mpf.rel: $(KNLMPFDIR)/kcre_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/kcre_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_mpf.rel: $(KNLMPFDIR)/del_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/del_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

get_mpf.rel: $(KNLMPFDIR)/get_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/get_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

pget_mpf.rel: $(KNLMPFDIR)/pget_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/pget_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

tget_mpf.rel: $(KNLMPFDIR)/tget_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/tget_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rel_mpf.rel: $(KNLMPFDIR)/rel_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/rel_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_mpf.rel: $(KNLMPFDIR)/ref_mpf.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLMPFDIR)/ref_mpf.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# 時間管理
ini_tim.rel: $(KNLTIMDIR)/ini_tim.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/ini_tim.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

set_tim.rel: $(KNLTIMDIR)/set_tim.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/set_tim.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

get_tim.rel: $(KNLTIMDIR)/get_tim.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/get_tim.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

isig_tim.rel: $(KNLTIMDIR)/isig_tim.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/isig_tim.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

add_tml.rel: $(KNLTIMDIR)/add_tml.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/add_tml.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rmv_tml.rel: $(KNLTIMDIR)/rmv_tml.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLTIMDIR)/rmv_tml.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# 周期ハンドラ
ini_cyc.rel: $(KNLCYCDIR)/ini_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/ini_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cyc_hdr.rel: $(KNLCYCDIR)/cyc_hdr.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/cyc_hdr.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sta_cyc.rel: $(KNLCYCDIR)/sta_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/sta_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

stp_cyc.rel: $(KNLCYCDIR)/stp_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/stp_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

cre_cyc.rel: $(KNLCYCDIR)/cre_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/cre_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

acre_cyc.rel: $(KNLCYCDIR)/acre_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/acre_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kcre_cyc.rel: $(KNLCYCDIR)/kcre_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/kcre_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

del_cyc.rel: $(KNLCYCDIR)/del_cyc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLCYCDIR)/del_cyc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# アラームハンドラ
ini_alm.rel: $(KNLALMDIR)/ini_alm.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLALMDIR)/ini_alm.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

alm_hdr.rel: $(KNLALMDIR)/alm_hdr.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLALMDIR)/alm_hdr.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sta_alm.rel: $(KNLALMDIR)/sta_alm.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLALMDIR)/sta_alm.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

stp_alm.rel: $(KNLALMDIR)/stp_alm.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLALMDIR)/stp_alm.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# 割り込み管理
ram_int.rel: $(KNLINTDIR)/ram_int.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLINTDIR)/ram_int.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

exe_int.rel: $(KNLINTDIR)/exe_int.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLINTDIR)/exe_int.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm


# システム状態管理
get_tid.rel: $(KNLSYSDIR)/get_tid.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/get_tid.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

kget_tid.rel: $(KNLSYSDIR)/kget_tid.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/kget_tid.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

rot_rdq.rel: $(KNLSYSDIR)/rot_rdq.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/rot_rdq.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

loc_cpu.rel: $(KNLSYSDIR)/loc_cpu.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/loc_cpu.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

unl_cpu.rel: $(KNLSYSDIR)/unl_cpu.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/unl_cpu.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

dis_dsp.rel: $(KNLSYSDIR)/dis_dsp.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/dis_dsp.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ena_dsp.rel: $(KNLSYSDIR)/ena_dsp.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/ena_dsp.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sns_ctx.rel: $(KNLSYSDIR)/sns_ctx.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/sns_ctx.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sns_loc.rel: $(KNLSYSDIR)/sns_loc.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/sns_loc.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sns_dsp.rel: $(KNLSYSDIR)/sns_dsp.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/sns_dsp.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

sns_dpn.rel: $(KNLSYSDIR)/sns_dpn.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/sns_dpn.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

ref_ver.rel: $(KNLSYSDIR)/ref_ver.c $(INCS)
	$(CC) $(CFLAGS) -no -a_tmp.asm $(KNLSYSDIR)/ref_ver.c
	$(ASM) $(AFLAGS) -o$@ _tmp.asm

clean:
	rm -f $(OBJS) pacctx.rel pacint.rel _tmp.asm *~

install:
	cp $(LIB) $(TOOLDIR2)/lib78k0r

#	-------------------------------------------------------------------------
#		Copyright (C) 1998-2009 by Project HOS
#	-------------------------------------------------------------------------
