# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                     
#   ライブラリメイクファイル SH2 gcc用                                        
#                                                                             
#                                     Copyright (C) 1998-2002 by Project HOS  
#                                     http://sourceforge.jp/projects/hos/     
# --------------------------------------------------------------------------- 



# パス定義
HOSROOT    = ../../..
INCDIR     = $(HOSROOT)/include
SRCDIR     = $(HOSROOT)/src
PACDIR     = $(SRCDIR)/sh
PACASMDIR  = $(PACDIR)/sh2gcc
MKNLDIR    = $(SRCDIR)/mknl
MKNLSYSDIR = $(MKNLDIR)/sys
MKNLTSKDIR = $(MKNLDIR)/tsk
MKNLQUEDIR = $(MKNLDIR)/que
MKNLTMODIR = $(MKNLDIR)/tmout
KERNELDIR  = $(SRCDIR)/kernel
KNLHOSDIR  = $(KERNELDIR)/hos
KNLMEMDIR  = $(KERNELDIR)/mem
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
CC     = sh-hms-gcc
ASM    = sh-hms-gcc
LIBR   = sh-hms-ar
RANLIB = sh-hms-ranlib


# オプション
CFLAGS = -c -O2 -m2 -D_HOS_ERCHK_LEVEL=3 -I$(INCDIR)
AFLAGS = -c


# ターゲット
TARGET  = libh4sh2e3.a


#インクルードファイル
INCS = $(INCDIR)/itron.h \
       $(INCDIR)/hoserchk.h \
       $(INCDIR)/hosdenv.h \
       $(INCDIR)/mknl.h \
       $(INCDIR)/kernel.h \
       $(INCDIR)/knl_hos.h \
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
OBJS = pacctx.o pacint.o pacimsk.o \
       mini_sys.o midl_lop.o msta_stu.o mext_stu.o \
       msta_tsk.o mter_tsk.o mchg_pri.o mrot_rdq.o \
       mwai_tsk.o mwup_tsk.o msus_tsk.o mrsm_tsk.o \
       mexe_dsp.o mdly_dsp.o msrh_top.o \
       mras_tex.o mexe_tex.o \
       madd_que.o madf_que.o madp_que.o mrmv_que.o \
       mrot_que.o mclr_que.o \
       mtic_tmo.o madd_tmo.o mrmv_tmo.o \
       sta_hos.o ini_mem.o alc_mem.o fre_mem.o \
       ini_tsk.o cre_tsk.o acre_tsk.o kcre_tsk.o del_tsk.o \
       act_tsk.o can_act.o sta_tsk.o ext_tsk.o exd_tsk.o \
       ter_tsk.o chg_pri.o get_pri.o ref_tst.o \
       slp_tsk.o tslp_tsk.o wup_tsk.o can_wup.o rel_wai.o \
       sus_tsk.o rsm_tsk.o frsm_tsk.o dly_tsk.o \
       ras_tex.o ktex_ent.o dis_tex.o ena_tex.o sns_tex.o \
       ini_sem.o cre_sem.o acre_sem.o kcre_sem.o del_sem.o \
       sig_sem.o wai_sem.o pol_sem.o twai_sem.o ref_sem.o \
       ini_flg.o cre_flg.o acre_flg.o kcre_flg.o del_flg.o \
       set_flg.o clr_flg.o wai_flg.o pol_flg.o \
       twai_flg.o chk_flg.o ref_flg.o \
       cre_dtq.o acre_dtq.o kcre_dtq.o del_dtq.o \
       snd_dtq.o psnd_dtq.o tsnd_dtq.o fsnd_dtq.o \
       rcv_dtq.o prcv_dtq.o trcv_dtq.o ref_dtq.o \
       cre_mbx.o acre_mbx.o kcre_mbx.o del_mbx.o \
       snd_mbx.o rcv_mbx.o prcv_mbx.o trcv_mbx.o ref_mbx.o \
       ini_mbf.o cre_mbf.o acre_mbf.o kcre_mbf.o del_mbf.o \
       snd_mbf.o psnd_mbf.o tsnd_mbf.o ksnd_mbf.o \
       rcv_mbf.o prcv_mbf.o trcv_mbf.o krcv_mbf.o ref_mbf.o \
       ini_mpf.o cre_mpf.o acre_mpf.o kcre_mpf.o del_mpf.o \
       get_mpf.o pget_mpf.o tget_mpf.o rel_mpf.o ref_mpf.o \
       ini_tim.o isig_tim.o set_tim.o get_tim.o \
       add_tml.o rmv_tml.o \
       ini_cyc.o cyc_hdr.o sta_cyc.o stp_cyc.o \
       cre_cyc.o acre_cyc.o kcre_cyc.o del_cyc.o \
       ini_alm.o alm_hdr.o sta_alm.o stp_alm.o \
       ram_int.o exe_int.o \
       get_tid.o kget_tid.o rot_rdq.o \
       loc_cpu.o unl_cpu.o dis_dsp.o ena_dsp.o \
       sns_ctx.o sns_loc.o sns_dsp.o sns_dpn.o \
       ref_ver.o


# ライブラリ生成
$(TARGET): $(OBJS)
	$(LIBR) rc $(TARGET) $(OBJS)
	$(RANLIB) $(TARGET)
	rm -f $(OBJS)


# プロセッサ依存
pacctx.o: $(PACASMDIR)/pacctx.s
	$(ASM) $(AFLAGS) -o pacctx.o $(PACASMDIR)/pacctx.s

pacint.o: $(PACASMDIR)/pacint.s
	$(ASM) $(AFLAGS) -o pacint.o $(PACASMDIR)/pacint.s

pacimsk.o: $(PACDIR)/pacimsk.c
	$(CC) $(CFLAGS) $(PACDIR)/pacimsk.c


# μカーネル システム制御
mini_sys.o: $(MKNLSYSDIR)/mini_sys.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)/mini_sys.c

midl_lop.o: $(MKNLSYSDIR)/midl_lop.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)/midl_lop.c

msta_stu.o: $(MKNLSYSDIR)/msta_stu.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)/msta_stu.c

mext_stu.o: $(MKNLSYSDIR)/mext_stu.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)/mext_stu.c


# μカーネル タスク制御
msta_tsk.o: $(MKNLTSKDIR)/msta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/msta_tsk.c

mter_tsk.o: $(MKNLTSKDIR)/mter_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mter_tsk.c

mchg_pri.o: $(MKNLTSKDIR)/mchg_pri.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mchg_pri.c

mrot_rdq.o: $(MKNLTSKDIR)/mrot_rdq.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mrot_rdq.c

mwai_tsk.o: $(MKNLTSKDIR)/mwai_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mwai_tsk.c

mwup_tsk.o: $(MKNLTSKDIR)/mwup_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mwup_tsk.c

msus_tsk.o: $(MKNLTSKDIR)/msus_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/msus_tsk.c

mrsm_tsk.o: $(MKNLTSKDIR)/mrsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mrsm_tsk.c

mexe_dsp.o: $(MKNLTSKDIR)/mexe_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mexe_dsp.c

mdly_dsp.o: $(MKNLTSKDIR)/mdly_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mdly_dsp.c

msrh_top.o: $(MKNLTSKDIR)/msrh_top.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/msrh_top.c

mras_tex.o: $(MKNLTSKDIR)/mras_tex.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mras_tex.c

mexe_tex.o: $(MKNLTSKDIR)/mexe_tex.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)/mexe_tex.c


# μカーネル タスクキュー管理
madd_que.o: $(MKNLQUEDIR)/madd_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/madd_que.c

madf_que.o: $(MKNLQUEDIR)/madf_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/madf_que.c

madp_que.o: $(MKNLQUEDIR)/madp_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/madp_que.c

mrmv_que.o: $(MKNLQUEDIR)/mrmv_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/mrmv_que.c

mrot_que.o: $(MKNLQUEDIR)/mrot_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/mrot_que.c

mclr_que.o: $(MKNLQUEDIR)/mclr_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)/mclr_que.c


# μカーネル タイムアウトキュー管理
mtic_tmo.o: $(MKNLTMODIR)/mtic_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)/mtic_tmo.c

madd_tmo.o: $(MKNLTMODIR)/madd_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)/madd_tmo.c

mrmv_tmo.o: $(MKNLTMODIR)/mrmv_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)/mrmv_tmo.c


# カーネル固有
sta_hos.o: $(KNLHOSDIR)/sta_hos.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)/sta_hos.c


# カーネルメモリ管理
ini_mem.o: $(KNLMEMDIR)/ini_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)/ini_mem.c

alc_mem.o: $(KNLMEMDIR)/alc_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)/alc_mem.c

fre_mem.o: $(KNLMEMDIR)/fre_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)/fre_mem.c 


# タスク
ini_tsk.o: $(KNLTSKDIR)/ini_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ini_tsk.c

cre_tsk.o: $(KNLTSKDIR)/cre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/cre_tsk.c

acre_tsk.o: $(KNLTSKDIR)/acre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/acre_tsk.c

kcre_tsk.o: $(KNLTSKDIR)/kcre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/kcre_tsk.c

del_tsk.o: $(KNLTSKDIR)/del_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/del_tsk.c

act_tsk.o: $(KNLTSKDIR)/act_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/act_tsk.c

can_act.o: $(KNLTSKDIR)/can_act.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/can_act.c

sta_tsk.o: $(KNLTSKDIR)/sta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/sta_tsk.c

ext_tsk.o: $(KNLTSKDIR)/ext_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ext_tsk.c

exd_tsk.o: $(KNLTSKDIR)/exd_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/exd_tsk.c

ter_tsk.o: $(KNLTSKDIR)/ter_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ter_tsk.c

chg_pri.o: $(KNLTSKDIR)/chg_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/chg_pri.c

get_pri.o: $(KNLTSKDIR)/get_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/get_pri.c

ref_tst.o: $(KNLTSKDIR)/ref_tst.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ref_tst.c

slp_tsk.o: $(KNLTSKDIR)/slp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/slp_tsk.c

tslp_tsk.o: $(KNLTSKDIR)/tslp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/tslp_tsk.c

wup_tsk.o: $(KNLTSKDIR)/wup_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/wup_tsk.c

can_wup.o: $(KNLTSKDIR)/can_wup.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/can_wup.c

rel_wai.o: $(KNLTSKDIR)/rel_wai.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/rel_wai.c

sus_tsk.o: $(KNLTSKDIR)/sus_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/sus_tsk.c

rsm_tsk.o: $(KNLTSKDIR)/rsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/rsm_tsk.c

frsm_tsk.o: $(KNLTSKDIR)/frsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/frsm_tsk.c

dly_tsk.o: $(KNLTSKDIR)/dly_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/dly_tsk.c

ktex_ent.o: $(KNLTSKDIR)/ktex_ent.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ktex_ent.c

ras_tex.o: $(KNLTSKDIR)/ras_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ras_tex.c

dis_tex.o: $(KNLTSKDIR)/dis_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/dis_tex.c

ena_tex.o: $(KNLTSKDIR)/ena_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/ena_tex.c

sns_tex.o: $(KNLTSKDIR)/sns_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)/sns_tex.c


# セマフォ
ini_sem.o: $(KNLSEMDIR)/ini_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/ini_sem.c

cre_sem.o: $(KNLSEMDIR)/cre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/cre_sem.c

acre_sem.o: $(KNLSEMDIR)/acre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/acre_sem.c

kcre_sem.o: $(KNLSEMDIR)/kcre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/kcre_sem.c

del_sem.o: $(KNLSEMDIR)/del_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/del_sem.c

sig_sem.o: $(KNLSEMDIR)/sig_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/sig_sem.c

wai_sem.o: $(KNLSEMDIR)/wai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/wai_sem.c

pol_sem.o: $(KNLSEMDIR)/pol_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/pol_sem.c

twai_sem.o: $(KNLSEMDIR)/twai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/twai_sem.c

ref_sem.o: $(KNLSEMDIR)/ref_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)/ref_sem.c


# イベントフラグ
ini_flg.o: $(KNLFLGDIR)/ini_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/ini_flg.c

cre_flg.o: $(KNLFLGDIR)/cre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/cre_flg.c

acre_flg.o: $(KNLFLGDIR)/acre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/acre_flg.c

kcre_flg.o: $(KNLFLGDIR)/kcre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/kcre_flg.c

del_flg.o: $(KNLFLGDIR)/del_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/del_flg.c

set_flg.o: $(KNLFLGDIR)/set_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/set_flg.c

clr_flg.o: $(KNLFLGDIR)/clr_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/clr_flg.c

wai_flg.o: $(KNLFLGDIR)/wai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/wai_flg.c

pol_flg.o: $(KNLFLGDIR)/pol_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/pol_flg.c

twai_flg.o: $(KNLFLGDIR)/twai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/twai_flg.c

chk_flg.o: $(KNLFLGDIR)/chk_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/chk_flg.c

ref_flg.o: $(KNLFLGDIR)/ref_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)/ref_flg.c


# データキュー
cre_dtq.o: $(KNLDTQDIR)/cre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/cre_dtq.c

acre_dtq.o: $(KNLDTQDIR)/acre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/acre_dtq.c

kcre_dtq.o: $(KNLDTQDIR)/kcre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/kcre_dtq.c

del_dtq.o: $(KNLDTQDIR)/del_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/del_dtq.c

snd_dtq.o: $(KNLDTQDIR)/snd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/snd_dtq.c

psnd_dtq.o: $(KNLDTQDIR)/psnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/psnd_dtq.c

tsnd_dtq.o: $(KNLDTQDIR)/tsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/tsnd_dtq.c

fsnd_dtq.o: $(KNLDTQDIR)/fsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/fsnd_dtq.c

rcv_dtq.o: $(KNLDTQDIR)/rcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/rcv_dtq.c

prcv_dtq.o: $(KNLDTQDIR)/prcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/prcv_dtq.c

trcv_dtq.o: $(KNLDTQDIR)/trcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/trcv_dtq.c

ref_dtq.o: $(KNLDTQDIR)/ref_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)/ref_dtq.c


# メールボックス
cre_mbx.o: $(KNLMBXDIR)/cre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/cre_mbx.c

acre_mbx.o: $(KNLMBXDIR)/acre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/acre_mbx.c

kcre_mbx.o: $(KNLMBXDIR)/kcre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/kcre_mbx.c

del_mbx.o: $(KNLMBXDIR)/del_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/del_mbx.c

snd_mbx.o: $(KNLMBXDIR)/snd_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/snd_mbx.c

rcv_mbx.o: $(KNLMBXDIR)/rcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/rcv_mbx.c

prcv_mbx.o: $(KNLMBXDIR)/prcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/prcv_mbx.c

trcv_mbx.o: $(KNLMBXDIR)/trcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/trcv_mbx.c

ref_mbx.o: $(KNLMBXDIR)/ref_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)/ref_mbx.c


# メッセージバッファ
ini_mbf.o: $(KNLMBFDIR)/ini_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/ini_mbf.c

cre_mbf.o: $(KNLMBFDIR)/cre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/cre_mbf.c

acre_mbf.o: $(KNLMBFDIR)/acre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/acre_mbf.c

kcre_mbf.o: $(KNLMBFDIR)/kcre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/kcre_mbf.c

del_mbf.o: $(KNLMBFDIR)/del_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/del_mbf.c

snd_mbf.o: $(KNLMBFDIR)/snd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/snd_mbf.c

psnd_mbf.o: $(KNLMBFDIR)/psnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/psnd_mbf.c

tsnd_mbf.o: $(KNLMBFDIR)/tsnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/tsnd_mbf.c

ksnd_mbf.o: $(KNLMBFDIR)/ksnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/ksnd_mbf.c

rcv_mbf.o: $(KNLMBFDIR)/rcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/rcv_mbf.c

prcv_mbf.o: $(KNLMBFDIR)/prcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/prcv_mbf.c

trcv_mbf.o: $(KNLMBFDIR)/trcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/trcv_mbf.c

krcv_mbf.o: $(KNLMBFDIR)/krcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/krcv_mbf.c

ref_mbf.o: $(KNLMBFDIR)/ref_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)/ref_mbf.c


# 固定長メモリプール
ini_mpf.o: $(KNLMPFDIR)/ini_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/ini_mpf.c

cre_mpf.o: $(KNLMPFDIR)/cre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/cre_mpf.c

acre_mpf.o: $(KNLMPFDIR)/acre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/acre_mpf.c

kcre_mpf.o: $(KNLMPFDIR)/kcre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/kcre_mpf.c

del_mpf.o: $(KNLMPFDIR)/del_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/del_mpf.c

get_mpf.o: $(KNLMPFDIR)/get_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/get_mpf.c

pget_mpf.o: $(KNLMPFDIR)/pget_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/pget_mpf.c

tget_mpf.o: $(KNLMPFDIR)/tget_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/tget_mpf.c

rel_mpf.o: $(KNLMPFDIR)/rel_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/rel_mpf.c

ref_mpf.o: $(KNLMPFDIR)/ref_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)/ref_mpf.c


# 時間管理
ini_tim.o: $(KNLTIMDIR)/ini_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/ini_tim.c

set_tim.o: $(KNLTIMDIR)/set_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/set_tim.c

get_tim.o: $(KNLTIMDIR)/get_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/get_tim.c

isig_tim.o: $(KNLTIMDIR)/isig_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/isig_tim.c

add_tml.o: $(KNLTIMDIR)/add_tml.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/add_tml.c

rmv_tml.o: $(KNLTIMDIR)/rmv_tml.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)/rmv_tml.c


# 周期ハンドラ
ini_cyc.o: $(KNLCYCDIR)/ini_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/ini_cyc.c

cyc_hdr.o: $(KNLCYCDIR)/cyc_hdr.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/cyc_hdr.c

sta_cyc.o: $(KNLCYCDIR)/sta_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/sta_cyc.c

stp_cyc.o: $(KNLCYCDIR)/stp_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/stp_cyc.c

cre_cyc.o: $(KNLCYCDIR)/cre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/cre_cyc.c

acre_cyc.o: $(KNLCYCDIR)/acre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/acre_cyc.c

kcre_cyc.o: $(KNLCYCDIR)/kcre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/kcre_cyc.c

del_cyc.o: $(KNLCYCDIR)/del_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)/del_cyc.c


# アラームハンドラ
ini_alm.o: $(KNLALMDIR)/ini_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)/ini_alm.c

alm_hdr.o: $(KNLALMDIR)/alm_hdr.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)/alm_hdr.c

sta_alm.o: $(KNLALMDIR)/sta_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)/sta_alm.c

stp_alm.o: $(KNLALMDIR)/stp_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)/stp_alm.c


# 割り込み管理
ram_int.o: $(KNLINTDIR)/ram_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)/ram_int.c

exe_int.o: $(KNLINTDIR)/exe_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)/exe_int.c


# システム状態管理
get_tid.o: $(KNLSYSDIR)/get_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/get_tid.c

kget_tid.o: $(KNLSYSDIR)/kget_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/kget_tid.c

rot_rdq.o: $(KNLSYSDIR)/rot_rdq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/rot_rdq.c

loc_cpu.o: $(KNLSYSDIR)/loc_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/loc_cpu.c

unl_cpu.o: $(KNLSYSDIR)/unl_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/unl_cpu.c

dis_dsp.o: $(KNLSYSDIR)/dis_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/dis_dsp.c

ena_dsp.o: $(KNLSYSDIR)/ena_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/ena_dsp.c

sns_ctx.o: $(KNLSYSDIR)/sns_ctx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/sns_ctx.c

sns_loc.o: $(KNLSYSDIR)/sns_loc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/sns_loc.c

sns_dsp.o: $(KNLSYSDIR)/sns_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/sns_dsp.c

sns_dpn.o: $(KNLSYSDIR)/sns_dpn.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/sns_dpn.c

ref_ver.o: $(KNLSYSDIR)/ref_ver.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)/ref_ver.c


clean:
	rm -f $(OBJS)
	rm -f $(TARGET)


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
