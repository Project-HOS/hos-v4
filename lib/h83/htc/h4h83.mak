# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   ライブラリメイクファイル H8/300H 日立コンパイラ用                          
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------



# パス定義
HOSROOT    = ..\..\..
INCDIR     = $(HOSROOT)\include
SRCDIR     = $(HOSROOT)\src
PACDIR     = $(SRCDIR)\h83
PACASMDIR  = $(SRCDIR)\h83\htc
KERNELDIR  = $(SRCDIR)\kernel
MKNLDIR    = $(SRCDIR)\mknl
MKNLSYSDIR = $(MKNLDIR)\sys
MKNLTSKDIR = $(MKNLDIR)\tsk
MKNLQUEDIR = $(MKNLDIR)\que
MKNLTMODIR = $(MKNLDIR)\tmout
KNLHOSDIR  = $(KERNELDIR)\hos
KNLHEPDIR  = $(KERNELDIR)\hep
KNLMEMDIR  = $(KERNELDIR)\mem
KNLTSKDIR  = $(KERNELDIR)\tsk
KNLSEMDIR  = $(KERNELDIR)\sem
KNLFLGDIR  = $(KERNELDIR)\flg
KNLDTQDIR  = $(KERNELDIR)\dtq
KNLMBXDIR  = $(KERNELDIR)\mbx
KNLMBFDIR  = $(KERNELDIR)\mbf
KNLMPFDIR  = $(KERNELDIR)\mpf
KNLTIMDIR  = $(KERNELDIR)\tim
KNLCYCDIR  = $(KERNELDIR)\cyc
KNLALMDIR  = $(KERNELDIR)\alm
KNLSYSDIR  = $(KERNELDIR)\sys
KNLINTDIR  = $(KERNELDIR)\int

# ツール
CC   = ch38
ASM  = asm38
LIBR = optlnk

# オプション
CFLAGS = -CPU=300HA -INCLUDE=$(INCDIR)
AFLAGS = 
LFLAGS = -FORM=Library

#インクルードファイル
INCS = $(INCDIR)\itron.h \
       $(INCDIR)\mknl.h \
       $(INCDIR)\kernel.h \
       $(INCDIR)\knl_hos.h \
       $(INCDIR)\knl_tsk.h \
       $(INCDIR)\knl_sem.h \
       $(INCDIR)\knl_flg.h \
       $(INCDIR)\knl_dtq.h \
       $(INCDIR)\knl_mbx.h \
       $(INCDIR)\knl_tim.h \
       $(INCDIR)\knl_sys.h \
       $(INCDIR)\knl_int.h \
       $(INCDIR)\h83\hospac.h


# オブジェクトファイル
OBJS = pacini.obj pacint.obj pacctx.obj \
       chg_imsk.obj get_imsk.obj fchg_imk.obj fget_imk.obj \
       mini_sys.obj mexe_sys.obj midl_lop.obj msta_stu.obj mext_stu.obj \
       msta_tsk.obj mter_tsk.obj mchg_pri.obj mrot_rdq.obj \
       mwai_tsk.obj mwup_tsk.obj msus_tsk.obj mrsm_tsk.obj \
       mexe_dsp.obj mdly_dsp.obj msrh_top.obj \
       mras_tex.obj mexe_tex.obj \
       madd_que.obj madf_que.obj madp_que.obj mrmv_que.obj \
       mrot_que.obj mclr_que.obj \
       mtic_tmo.obj madd_tmo.obj mrmv_tmo.obj \
       sta_hos.obj ini_mem.obj alc_mem.obj fre_mem.obj \
       cre_hep.obj alc_hep.obj fre_hep.obj \
       ini_tsk.obj cre_tsk.obj acre_tsk.obj kcre_tsk.obj del_tsk.obj \
       act_tsk.obj can_act.obj sta_tsk.obj ext_tsk.obj exd_tsk.obj \
       ter_tsk.obj chg_pri.obj get_pri.obj ref_tst.obj \
       slp_tsk.obj tslp_tsk.obj wup_tsk.obj can_wup.obj rel_wai.obj \
       sus_tsk.obj rsm_tsk.obj frsm_tsk.obj dly_tsk.obj \
       ras_tex.obj ktex_ent.obj dis_tex.obj ena_tex.obj sns_tex.obj \
       ini_sem.obj cre_sem.obj acre_sem.obj kcre_sem.obj del_sem.obj \
       sig_sem.obj wai_sem.obj pol_sem.obj twai_sem.obj ref_sem.obj \
       ini_flg.obj cre_flg.obj acre_flg.obj kcre_flg.obj del_flg.obj \
       set_flg.obj clr_flg.obj wai_flg.obj pol_flg.obj \
       twai_flg.obj chk_flg.obj ref_flg.obj \
       cre_dtq.obj acre_dtq.obj kcre_dtq.obj del_dtq.obj \
       snd_dtq.obj psnd_dtq.obj tsnd_dtq.obj fsnd_dtq.obj \
       rcv_dtq.obj prcv_dtq.obj trcv_dtq.obj ref_dtq.obj \
       cre_mbx.obj acre_mbx.obj kcre_mbx.obj del_mbx.obj \
       snd_mbx.obj rcv_mbx.obj prcv_mbx.obj trcv_mbx.obj ref_mbx.obj \
       ini_mbf.obj cre_mbf.obj acre_mbf.obj kcre_mbf.obj del_mbf.obj \
       snd_mbf.obj psnd_mbf.obj tsnd_mbf.obj ksnd_mbf.obj \
       rcv_mbf.obj prcv_mbf.obj trcv_mbf.obj krcv_mbf.obj ref_mbf.obj \
       ini_mpf.obj cre_mpf.obj acre_mpf.obj kcre_mpf.obj del_mpf.obj \
       get_mpf.obj pget_mpf.obj tget_mpf.obj rel_mpf.obj ref_mpf.obj \
       ini_tim.obj isig_tim.obj set_tim.obj get_tim.obj \
       add_tml.obj rmv_tml.obj \
       ini_cyc.obj cyc_hdr.obj sta_cyc.obj stp_cyc.obj \
       cre_cyc.obj acre_cyc.obj kcre_cyc.obj del_cyc.obj \
       ini_alm.obj alm_hdr.obj sta_alm.obj stp_alm.obj \
       ram_int.obj exe_int.obj \
       get_tid.obj kget_tid.obj rot_rdq.obj \
       loc_cpu.obj unl_cpu.obj dis_dsp.obj ena_dsp.obj \
       sns_ctx.obj sns_loc.obj sns_dsp.obj sns_dpn.obj \
       ref_ver.obj


# ターゲット
TARGET  = h4h83aki.lib


# ライブラリ
$(TARGET): $(OBJS)
	$(LIBR) $(LFLAGS) -OUTPUT=$(TARGET) $(OBJS)



# プロセッサ依存
pacini.obj: $(PACDIR)\pacini.c
	$(CC) $(CFLAGS) $(PACDIR)\pacini.c

pacctx.obj: $(PACASMDIR)\pacctx.src
	$(ASM) $(AFLAGS) $(PACASMDIR)\pacctx.src
	move $(PACASMDIR)\pacctx.obj .

pacint.obj: $(PACASMDIR)\pacint.src
	$(ASM) $(AFLAGS) $(PACASMDIR)\pacint.src
	move $(PACASMDIR)\pacint.obj .

chg_imsk.obj: $(PACDIR)\chg_imsk.c
	$(CC) $(CFLAGS) $(PACDIR)\chg_imsk.c

get_imsk.obj: $(PACDIR)\get_imsk.c
	$(CC) $(CFLAGS) $(PACDIR)\get_imsk.c

fchg_imk.obj: $(PACDIR)\fchg_imk.c
	$(CC) $(CFLAGS) $(PACDIR)\fchg_imk.c

fget_imk.obj: $(PACDIR)\fget_imk.c
	$(CC) $(CFLAGS) $(PACDIR)\fget_imk.c


# μカーネル システム制御
mini_sys.obj: $(MKNLSYSDIR)\mini_sys.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)\mini_sys.c

mexe_sys.obj: $(MKNLSYSDIR)\mexe_sys.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)\mexe_sys.c

midl_lop.obj: $(MKNLSYSDIR)\midl_lop.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)\midl_lop.c

msta_stu.obj: $(MKNLSYSDIR)\msta_stu.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)\msta_stu.c

mext_stu.obj: $(MKNLSYSDIR)\mext_stu.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLSYSDIR)\mext_stu.c


# μカーネル タスク制御
msta_tsk.obj: $(MKNLTSKDIR)\msta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\msta_tsk.c

mter_tsk.obj: $(MKNLTSKDIR)\mter_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mter_tsk.c

mchg_pri.obj: $(MKNLTSKDIR)\mchg_pri.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mchg_pri.c

mrot_rdq.obj: $(MKNLTSKDIR)\mrot_rdq.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mrot_rdq.c

mwai_tsk.obj: $(MKNLTSKDIR)\mwai_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mwai_tsk.c

mwup_tsk.obj: $(MKNLTSKDIR)\mwup_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mwup_tsk.c

msus_tsk.obj: $(MKNLTSKDIR)\msus_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\msus_tsk.c

mrsm_tsk.obj: $(MKNLTSKDIR)\mrsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mrsm_tsk.c

mexe_dsp.obj: $(MKNLTSKDIR)\mexe_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mexe_dsp.c

mdly_dsp.obj: $(MKNLTSKDIR)\mdly_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mdly_dsp.c

msrh_top.obj: $(MKNLTSKDIR)\msrh_top.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\msrh_top.c

mras_tex.obj: $(MKNLTSKDIR)\mras_tex.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mras_tex.c

mexe_tex.obj: $(MKNLTSKDIR)\mexe_tex.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTSKDIR)\mexe_tex.c


# μカーネル タスクキュー管理
madd_que.obj: $(MKNLQUEDIR)\madd_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\madd_que.c

madf_que.obj: $(MKNLQUEDIR)\madf_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\madf_que.c

madp_que.obj: $(MKNLQUEDIR)\madp_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\madp_que.c

mrmv_que.obj: $(MKNLQUEDIR)\mrmv_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\mrmv_que.c

mrot_que.obj: $(MKNLQUEDIR)\mrot_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\mrot_que.c

mclr_que.obj: $(MKNLQUEDIR)\mclr_que.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLQUEDIR)\mclr_que.c


# μカーネル タイムアウトキュー管理
mtic_tmo.obj: $(MKNLTMODIR)\mtic_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)\mtic_tmo.c

madd_tmo.obj: $(MKNLTMODIR)\madd_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)\madd_tmo.c

mrmv_tmo.obj: $(MKNLTMODIR)\mrmv_tmo.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLTMODIR)\mrmv_tmo.c


# HOS 固有
sta_hos.obj: $(KNLHOSDIR)\sta_hos.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\sta_hos.c


# メモリヒープ
cre_hep.obj: $(KNLHEPDIR)\cre_hep.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHEPDIR)\cre_hep.c

alc_hep.obj: $(KNLHEPDIR)\alc_hep.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHEPDIR)\alc_hep.c

fre_hep.obj: $(KNLHEPDIR)\fre_hep.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHEPDIR)\fre_hep.c 


# カーネルメモリ管理
ini_mem.obj: $(KNLMEMDIR)\ini_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)\ini_mem.c

alc_mem.obj: $(KNLMEMDIR)\alc_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)\alc_mem.c

fre_mem.obj: $(KNLMEMDIR)\fre_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMEMDIR)\fre_mem.c 


# タスク
ini_tsk.obj: $(KNLTSKDIR)\ini_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ini_tsk.c

cre_tsk.obj: $(KNLTSKDIR)\cre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\cre_tsk.c

acre_tsk.obj: $(KNLTSKDIR)\acre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\acre_tsk.c

kcre_tsk.obj: $(KNLTSKDIR)\kcre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\kcre_tsk.c

del_tsk.obj: $(KNLTSKDIR)\del_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\del_tsk.c

act_tsk.obj: $(KNLTSKDIR)\act_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\act_tsk.c

can_act.obj: $(KNLTSKDIR)\can_act.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\can_act.c

sta_tsk.obj: $(KNLTSKDIR)\sta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sta_tsk.c

ext_tsk.obj: $(KNLTSKDIR)\ext_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ext_tsk.c

exd_tsk.obj: $(KNLTSKDIR)\exd_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\exd_tsk.c

ter_tsk.obj: $(KNLTSKDIR)\ter_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ter_tsk.c

chg_pri.obj: $(KNLTSKDIR)\chg_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\chg_pri.c

get_pri.obj: $(KNLTSKDIR)\get_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\get_pri.c

ref_tst.obj: $(KNLTSKDIR)\ref_tst.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ref_tst.c

slp_tsk.obj: $(KNLTSKDIR)\slp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\slp_tsk.c

tslp_tsk.obj: $(KNLTSKDIR)\tslp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\tslp_tsk.c

wup_tsk.obj: $(KNLTSKDIR)\wup_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\wup_tsk.c

can_wup.obj: $(KNLTSKDIR)\can_wup.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\can_wup.c

rel_wai.obj: $(KNLTSKDIR)\rel_wai.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\rel_wai.c

sus_tsk.obj: $(KNLTSKDIR)\sus_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sus_tsk.c

rsm_tsk.obj: $(KNLTSKDIR)\rsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\rsm_tsk.c

frsm_tsk.obj: $(KNLTSKDIR)\frsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\frsm_tsk.c

dly_tsk.obj: $(KNLTSKDIR)\dly_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\dly_tsk.c

ras_tex.obj: $(KNLTSKDIR)\ras_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ras_tex.c

ktex_ent.obj: $(KNLTSKDIR)\ktex_ent.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ktex_ent.c

dis_tex.obj: $(KNLTSKDIR)\dis_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\dis_tex.c

ena_tex.obj: $(KNLTSKDIR)\ena_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ena_tex.c

sns_tex.obj: $(KNLTSKDIR)\sns_tex.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sns_tex.c


# セマフォ
ini_sem.obj: $(KNLSEMDIR)\ini_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\ini_sem.c

cre_sem.obj: $(KNLSEMDIR)\cre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\cre_sem.c

acre_sem.obj: $(KNLSEMDIR)\acre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\acre_sem.c

kcre_sem.obj: $(KNLSEMDIR)\kcre_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\kcre_sem.c

del_sem.obj: $(KNLSEMDIR)\del_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\del_sem.c

sig_sem.obj: $(KNLSEMDIR)\sig_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\sig_sem.c

wai_sem.obj: $(KNLSEMDIR)\wai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\wai_sem.c

pol_sem.obj: $(KNLSEMDIR)\pol_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\pol_sem.c

twai_sem.obj: $(KNLSEMDIR)\twai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\twai_sem.c

ref_sem.obj: $(KNLSEMDIR)\ref_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\ref_sem.c


# イベントフラグ
ini_flg.obj: $(KNLFLGDIR)\ini_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\ini_flg.c

cre_flg.obj: $(KNLFLGDIR)\cre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\cre_flg.c

acre_flg.obj: $(KNLFLGDIR)\acre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\acre_flg.c

kcre_flg.obj: $(KNLFLGDIR)\kcre_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\kcre_flg.c

del_flg.obj: $(KNLFLGDIR)\del_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\del_flg.c

set_flg.obj: $(KNLFLGDIR)\set_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\set_flg.c

clr_flg.obj: $(KNLFLGDIR)\clr_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\clr_flg.c

wai_flg.obj: $(KNLFLGDIR)\wai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\wai_flg.c

pol_flg.obj: $(KNLFLGDIR)\pol_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\pol_flg.c

twai_flg.obj: $(KNLFLGDIR)\twai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\twai_flg.c

chk_flg.obj: $(KNLFLGDIR)\chk_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\chk_flg.c

ref_flg.obj: $(KNLFLGDIR)\ref_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\ref_flg.c


# データキュー
cre_dtq.obj: $(KNLDTQDIR)\cre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\cre_dtq.c

acre_dtq.obj: $(KNLDTQDIR)\acre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\acre_dtq.c

kcre_dtq.obj: $(KNLDTQDIR)\kcre_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\kcre_dtq.c

del_dtq.obj: $(KNLDTQDIR)\del_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\del_dtq.c

snd_dtq.obj: $(KNLDTQDIR)\snd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\snd_dtq.c

psnd_dtq.obj: $(KNLDTQDIR)\psnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\psnd_dtq.c

tsnd_dtq.obj: $(KNLDTQDIR)\tsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\tsnd_dtq.c

fsnd_dtq.obj: $(KNLDTQDIR)\fsnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\fsnd_dtq.c

rcv_dtq.obj: $(KNLDTQDIR)\rcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\rcv_dtq.c

prcv_dtq.obj: $(KNLDTQDIR)\prcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\prcv_dtq.c

trcv_dtq.obj: $(KNLDTQDIR)\trcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\trcv_dtq.c

ref_dtq.obj: $(KNLDTQDIR)\ref_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\ref_dtq.c


# メールボックス
cre_mbx.obj: $(KNLMBXDIR)\cre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\cre_mbx.c

acre_mbx.obj: $(KNLMBXDIR)\acre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\acre_mbx.c

kcre_mbx.obj: $(KNLMBXDIR)\kcre_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\kcre_mbx.c

del_mbx.obj: $(KNLMBXDIR)\del_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\del_mbx.c

snd_mbx.obj: $(KNLMBXDIR)\snd_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\snd_mbx.c

rcv_mbx.obj: $(KNLMBXDIR)\rcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\rcv_mbx.c

prcv_mbx.obj: $(KNLMBXDIR)\prcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\prcv_mbx.c

trcv_mbx.obj: $(KNLMBXDIR)\trcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\trcv_mbx.c

ref_mbx.obj: $(KNLMBXDIR)\ref_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\ref_mbx.c


# メッセージバッファ
ini_mbf.obj: $(KNLMBFDIR)\ini_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\ini_mbf.c

cre_mbf.obj: $(KNLMBFDIR)\cre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\cre_mbf.c

acre_mbf.obj: $(KNLMBFDIR)\acre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\acre_mbf.c

kcre_mbf.obj: $(KNLMBFDIR)\kcre_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\kcre_mbf.c

del_mbf.obj: $(KNLMBFDIR)\del_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\del_mbf.c

snd_mbf.obj: $(KNLMBFDIR)\snd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\snd_mbf.c

psnd_mbf.obj: $(KNLMBFDIR)\psnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\psnd_mbf.c

tsnd_mbf.obj: $(KNLMBFDIR)\tsnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\tsnd_mbf.c

ksnd_mbf.obj: $(KNLMBFDIR)\ksnd_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\ksnd_mbf.c

rcv_mbf.obj: $(KNLMBFDIR)\rcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\rcv_mbf.c

prcv_mbf.obj: $(KNLMBFDIR)\prcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\prcv_mbf.c

trcv_mbf.obj: $(KNLMBFDIR)\trcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\trcv_mbf.c

krcv_mbf.obj: $(KNLMBFDIR)\krcv_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\krcv_mbf.c

ref_mbf.obj: $(KNLMBFDIR)\ref_mbf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBFDIR)\ref_mbf.c


# 固定長メモリプール
ini_mpf.obj: $(KNLMPFDIR)\ini_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\ini_mpf.c

cre_mpf.obj: $(KNLMPFDIR)\cre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\cre_mpf.c

acre_mpf.obj: $(KNLMPFDIR)\acre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\acre_mpf.c

kcre_mpf.obj: $(KNLMPFDIR)\kcre_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\kcre_mpf.c

del_mpf.obj: $(KNLMPFDIR)\del_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\del_mpf.c

get_mpf.obj: $(KNLMPFDIR)\get_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\get_mpf.c

pget_mpf.obj: $(KNLMPFDIR)\pget_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\pget_mpf.c

tget_mpf.obj: $(KNLMPFDIR)\tget_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\tget_mpf.c

rel_mpf.obj: $(KNLMPFDIR)\rel_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\rel_mpf.c

ref_mpf.obj: $(KNLMPFDIR)\ref_mpf.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMPFDIR)\ref_mpf.c


# 時間管理
ini_tim.obj: $(KNLTIMDIR)\ini_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\ini_tim.c

set_tim.obj: $(KNLTIMDIR)\set_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\set_tim.c

get_tim.obj: $(KNLTIMDIR)\get_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\get_tim.c

isig_tim.obj: $(KNLTIMDIR)\isig_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\isig_tim.c

add_tml.obj: $(KNLTIMDIR)\add_tml.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\add_tml.c

rmv_tml.obj: $(KNLTIMDIR)\rmv_tml.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\rmv_tml.c


# 周期ハンドラ
ini_cyc.obj: $(KNLCYCDIR)\ini_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\ini_cyc.c

cyc_hdr.obj: $(KNLCYCDIR)\cyc_hdr.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\cyc_hdr.c

sta_cyc.obj: $(KNLCYCDIR)\sta_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\sta_cyc.c

stp_cyc.obj: $(KNLCYCDIR)\stp_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\stp_cyc.c

cre_cyc.obj: $(KNLCYCDIR)\cre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\cre_cyc.c

acre_cyc.obj: $(KNLCYCDIR)\acre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\acre_cyc.c

kcre_cyc.obj: $(KNLCYCDIR)\kcre_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\kcre_cyc.c

del_cyc.obj: $(KNLCYCDIR)\del_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLCYCDIR)\del_cyc.c


# アラームハンドラ
ini_alm.obj: $(KNLALMDIR)\ini_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)\ini_alm.c

alm_hdr.obj: $(KNLALMDIR)\alm_hdr.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)\alm_hdr.c

sta_alm.obj: $(KNLALMDIR)\sta_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)\sta_alm.c

stp_alm.obj: $(KNLALMDIR)\stp_alm.c $(INCS)
	$(CC) $(CFLAGS) $(KNLALMDIR)\stp_alm.c


# 割り込み管理
ram_int.obj: $(KNLINTDIR)\ram_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)\ram_int.c

exe_int.obj: $(KNLINTDIR)\exe_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)\exe_int.c


# システム状態管理
get_tid.obj: $(KNLSYSDIR)\get_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\get_tid.c

kget_tid.obj: $(KNLSYSDIR)\kget_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\kget_tid.c

rot_rdq.obj: $(KNLSYSDIR)\rot_rdq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\rot_rdq.c

loc_cpu.obj: $(KNLSYSDIR)\loc_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\loc_cpu.c

unl_cpu.obj: $(KNLSYSDIR)\unl_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\unl_cpu.c

dis_dsp.obj: $(KNLSYSDIR)\dis_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\dis_dsp.c

ena_dsp.obj: $(KNLSYSDIR)\ena_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\ena_dsp.c

sns_ctx.obj: $(KNLSYSDIR)\sns_ctx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_ctx.c

sns_loc.obj: $(KNLSYSDIR)\sns_loc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_loc.c

sns_dsp.obj: $(KNLSYSDIR)\sns_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_dsp.c

sns_dpn.obj: $(KNLSYSDIR)\sns_dpn.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_dpn.c

ref_ver.obj: $(KNLSYSDIR)\ref_ver.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\ref_ver.c


clean:
	del *.lib
	del *.lst
	del *.obj


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
