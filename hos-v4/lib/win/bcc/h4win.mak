# -----------------------------------------------------------------------------
#  HOS-V4 Win版                                                                
#   ライブラリメイクファイル Borland-C++ Ver.5.5 コンパイラ用                  
#                                                                              
#                                       Copyright (C) 1998-2003 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------


# パス定義
OBJSDIR    = objs
HOSROOT    = ..\..\..
INCDIR     = $(HOSROOT)\include
PACINCDIR  = $(INCDIR)\win
SRCDIR     = $(HOSROOT)\src
PACDIR     = $(SRCDIR)\win
MKNLDIR    = $(SRCDIR)\mknl
KERNELDIR  = $(SRCDIR)\kernel
MKNLSYSDIR = $(MKNLDIR)\sys
MKNLTSKDIR = $(MKNLDIR)\tsk
MKNLQUEDIR = $(MKNLDIR)\que
MKNLTMODIR = $(MKNLDIR)\tmout
KNLHOSDIR  = $(KERNELDIR)\hos
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
CC     = bcc32
LIBR   = tlib

# オプション
CFLAGS = -c -w-8057 -w-8064 -I$(INCDIR) -I$(PACINCDIR)
AFLAGS = 
LFLAGS = 

# ターゲット
TARGET = h4win.lib

#インクルードファイル
INCS = $(INCDIR)\win\hospac.h \
       $(INCDIR)\itron.h \
       $(INCDIR)\hosdenv.h \
       $(INCDIR)\hoserchk.h \
       $(INCDIR)\mknl.h \
       $(INCDIR)\kernel.h \
       $(INCDIR)\knl_hos.h \
       $(INCDIR)\knl_mem.h \
       $(INCDIR)\knl_tsk.h \
       $(INCDIR)\knl_sem.h \
       $(INCDIR)\knl_flg.h \
       $(INCDIR)\knl_dtq.h \
       $(INCDIR)\knl_mbx.h \
       $(INCDIR)\knl_mpf.h \
       $(INCDIR)\knl_mbf.h \
       $(INCDIR)\knl_tim.h \
       $(INCDIR)\knl_cyc.h \
       $(INCDIR)\knl_alm.h \
       $(INCDIR)\knl_sys.h \
       $(INCDIR)\knl_int.h \
       $(INCDIR)\knl_exc.h

# オブジェクトファイル
OBJS = $(OBJSDIR)\pacint.obj \
       $(OBJSDIR)\hospac.obj \
       $(OBJSDIR)\mini_sys.obj \
       $(OBJSDIR)\midl_lop.obj \
       $(OBJSDIR)\msta_stu.obj \
       $(OBJSDIR)\mext_stu.obj \
       $(OBJSDIR)\msta_tsk.obj \
       $(OBJSDIR)\mter_tsk.obj \
       $(OBJSDIR)\mchg_pri.obj \
       $(OBJSDIR)\mrot_rdq.obj \
       $(OBJSDIR)\mwai_tsk.obj \
       $(OBJSDIR)\mwup_tsk.obj \
       $(OBJSDIR)\msus_tsk.obj \
       $(OBJSDIR)\mrsm_tsk.obj \
       $(OBJSDIR)\mexe_dsp.obj \
       $(OBJSDIR)\mdly_dsp.obj \
       $(OBJSDIR)\msrh_top.obj \
       $(OBJSDIR)\mras_tex.obj \
       $(OBJSDIR)\mexe_tex.obj \
       $(OBJSDIR)\madd_que.obj \
       $(OBJSDIR)\madf_que.obj \
       $(OBJSDIR)\madp_que.obj \
       $(OBJSDIR)\mrmv_que.obj \
       $(OBJSDIR)\mrot_que.obj \
       $(OBJSDIR)\mclr_que.obj \
       $(OBJSDIR)\mtic_tmo.obj \
       $(OBJSDIR)\madd_tmo.obj \
       $(OBJSDIR)\mrmv_tmo.obj \
       $(OBJSDIR)\sta_hos.obj \
       $(OBJSDIR)\ini_mem.obj \
       $(OBJSDIR)\alc_mem.obj \
       $(OBJSDIR)\fre_mem.obj \
       $(OBJSDIR)\ini_tsk.obj \
       $(OBJSDIR)\cre_tsk.obj \
       $(OBJSDIR)\acre_tsk.obj \
       $(OBJSDIR)\kcre_tsk.obj \
       $(OBJSDIR)\del_tsk.obj \
       $(OBJSDIR)\act_tsk.obj \
       $(OBJSDIR)\can_act.obj \
       $(OBJSDIR)\sta_tsk.obj \
       $(OBJSDIR)\ext_tsk.obj \
       $(OBJSDIR)\exd_tsk.obj \
       $(OBJSDIR)\ter_tsk.obj \
       $(OBJSDIR)\chg_pri.obj \
       $(OBJSDIR)\get_pri.obj \
       $(OBJSDIR)\ref_tst.obj \
       $(OBJSDIR)\slp_tsk.obj \
       $(OBJSDIR)\tslp_tsk.obj \
       $(OBJSDIR)\wup_tsk.obj \
       $(OBJSDIR)\can_wup.obj \
       $(OBJSDIR)\rel_wai.obj \
       $(OBJSDIR)\sus_tsk.obj \
       $(OBJSDIR)\rsm_tsk.obj \
       $(OBJSDIR)\frsm_tsk.obj \
       $(OBJSDIR)\dly_tsk.obj \
       $(OBJSDIR)\ras_tex.obj \
       $(OBJSDIR)\ktex_ent.obj \
       $(OBJSDIR)\dis_tex.obj \
       $(OBJSDIR)\ena_tex.obj \
       $(OBJSDIR)\sns_tex.obj \
       $(OBJSDIR)\ini_sem.obj \
       $(OBJSDIR)\cre_sem.obj \
       $(OBJSDIR)\acre_sem.obj \
       $(OBJSDIR)\kcre_sem.obj \
       $(OBJSDIR)\del_sem.obj \
       $(OBJSDIR)\sig_sem.obj \
       $(OBJSDIR)\wai_sem.obj \
       $(OBJSDIR)\pol_sem.obj \
       $(OBJSDIR)\twai_sem.obj \
       $(OBJSDIR)\ref_sem.obj \
       $(OBJSDIR)\ini_flg.obj \
       $(OBJSDIR)\cre_flg.obj \
       $(OBJSDIR)\acre_flg.obj \
       $(OBJSDIR)\kcre_flg.obj \
       $(OBJSDIR)\del_flg.obj \
       $(OBJSDIR)\set_flg.obj \
       $(OBJSDIR)\clr_flg.obj \
       $(OBJSDIR)\wai_flg.obj \
       $(OBJSDIR)\pol_flg.obj \
       $(OBJSDIR)\twai_flg.obj \
       $(OBJSDIR)\chk_flg.obj \
       $(OBJSDIR)\ref_flg.obj \
       $(OBJSDIR)\cre_dtq.obj \
       $(OBJSDIR)\acre_dtq.obj \
       $(OBJSDIR)\kcre_dtq.obj \
       $(OBJSDIR)\del_dtq.obj \
       $(OBJSDIR)\snd_dtq.obj \
       $(OBJSDIR)\psnd_dtq.obj \
       $(OBJSDIR)\tsnd_dtq.obj \
       $(OBJSDIR)\fsnd_dtq.obj \
       $(OBJSDIR)\rcv_dtq.obj \
       $(OBJSDIR)\prcv_dtq.obj \
       $(OBJSDIR)\trcv_dtq.obj \
       $(OBJSDIR)\ref_dtq.obj \
       $(OBJSDIR)\cre_mbx.obj \
       $(OBJSDIR)\acre_mbx.obj \
       $(OBJSDIR)\kcre_mbx.obj \
       $(OBJSDIR)\del_mbx.obj \
       $(OBJSDIR)\snd_mbx.obj \
       $(OBJSDIR)\rcv_mbx.obj \
       $(OBJSDIR)\prcv_mbx.obj \
       $(OBJSDIR)\trcv_mbx.obj \
       $(OBJSDIR)\ref_mbx.obj \
       $(OBJSDIR)\ini_mbf.obj \
       $(OBJSDIR)\cre_mbf.obj \
       $(OBJSDIR)\acre_mbf.obj \
       $(OBJSDIR)\kcre_mbf.obj \
       $(OBJSDIR)\del_mbf.obj \
       $(OBJSDIR)\snd_mbf.obj \
       $(OBJSDIR)\psnd_mbf.obj \
       $(OBJSDIR)\tsnd_mbf.obj \
       $(OBJSDIR)\ksnd_mbf.obj \
       $(OBJSDIR)\rcv_mbf.obj \
       $(OBJSDIR)\prcv_mbf.obj \
       $(OBJSDIR)\trcv_mbf.obj \
       $(OBJSDIR)\krcv_mbf.obj \
       $(OBJSDIR)\ref_mbf.obj \
       $(OBJSDIR)\ini_mpf.obj \
       $(OBJSDIR)\cre_mpf.obj \
       $(OBJSDIR)\acre_mpf.obj \
       $(OBJSDIR)\kcre_mpf.obj \
       $(OBJSDIR)\del_mpf.obj \
       $(OBJSDIR)\get_mpf.obj \
       $(OBJSDIR)\pget_mpf.obj \
       $(OBJSDIR)\tget_mpf.obj \
       $(OBJSDIR)\rel_mpf.obj \
       $(OBJSDIR)\ref_mpf.obj \
       $(OBJSDIR)\ini_tim.obj \
       $(OBJSDIR)\isig_tim.obj \
       $(OBJSDIR)\set_tim.obj \
       $(OBJSDIR)\get_tim.obj \
       $(OBJSDIR)\add_tml.obj \
       $(OBJSDIR)\rmv_tml.obj \
       $(OBJSDIR)\ini_cyc.obj \
       $(OBJSDIR)\cyc_hdr.obj \
       $(OBJSDIR)\sta_cyc.obj \
       $(OBJSDIR)\stp_cyc.obj \
       $(OBJSDIR)\cre_cyc.obj \
       $(OBJSDIR)\acre_cyc.obj \
       $(OBJSDIR)\kcre_cyc.obj \
       $(OBJSDIR)\del_cyc.obj \
       $(OBJSDIR)\ini_alm.obj \
       $(OBJSDIR)\alm_hdr.obj \
       $(OBJSDIR)\sta_alm.obj \
       $(OBJSDIR)\stp_alm.obj \
       $(OBJSDIR)\ram_int.obj \
       $(OBJSDIR)\exe_int.obj \
       $(OBJSDIR)\get_tid.obj \
       $(OBJSDIR)\kget_tid.obj \
       $(OBJSDIR)\rot_rdq.obj \
       $(OBJSDIR)\loc_cpu.obj \
       $(OBJSDIR)\unl_cpu.obj \
       $(OBJSDIR)\dis_dsp.obj \
       $(OBJSDIR)\ena_dsp.obj \
       $(OBJSDIR)\sns_ctx.obj \
       $(OBJSDIR)\sns_loc.obj \
       $(OBJSDIR)\sns_dsp.obj \
       $(OBJSDIR)\sns_dpn.obj \
       $(OBJSDIR)\ref_ver.obj


.suffixes:
.suffixes: .c


# all
all: mkobjdir $(TARGET)

# OBJ用ディレクトリ作成
mkobjdir:
	@if not exist $(OBJSDIR)  mkdir $(OBJSDIR)

# ライブラリ
$(TARGET): $(OBJS)
	$(LIBR)  $@ @&&!
+-$(**: = &^
+-)
!


# プロセッサ依存
$(OBJSDIR)\pacint.obj: $(PACDIR)\pacint.c $(INCS)
$(OBJSDIR)\hospac.obj: $(PACDIR)\hospac.c $(INCS)

# μカーネル システム制御
$(OBJSDIR)\mini_sys.obj: $(MKNLSYSDIR)\mini_sys.c $(INCS)
$(OBJSDIR)\midl_lop.obj: $(MKNLSYSDIR)\midl_lop.c $(INCS)
$(OBJSDIR)\msta_stu.obj: $(MKNLSYSDIR)\msta_stu.c $(INCS)
$(OBJSDIR)\mext_stu.obj: $(MKNLSYSDIR)\mext_stu.c $(INCS)

# μカーネル タスク制御
$(OBJSDIR)\msta_tsk.obj: $(MKNLTSKDIR)\msta_tsk.c $(INCS)
$(OBJSDIR)\mter_tsk.obj: $(MKNLTSKDIR)\mter_tsk.c $(INCS)
$(OBJSDIR)\mchg_pri.obj: $(MKNLTSKDIR)\mchg_pri.c $(INCS)
$(OBJSDIR)\mrot_rdq.obj: $(MKNLTSKDIR)\mrot_rdq.c $(INCS)
$(OBJSDIR)\mwai_tsk.obj: $(MKNLTSKDIR)\mwai_tsk.c $(INCS)
$(OBJSDIR)\mwup_tsk.obj: $(MKNLTSKDIR)\mwup_tsk.c $(INCS)
$(OBJSDIR)\msus_tsk.obj: $(MKNLTSKDIR)\msus_tsk.c $(INCS)
$(OBJSDIR)\mrsm_tsk.obj: $(MKNLTSKDIR)\mrsm_tsk.c $(INCS)
$(OBJSDIR)\mexe_dsp.obj: $(MKNLTSKDIR)\mexe_dsp.c $(INCS)
$(OBJSDIR)\mdly_dsp.obj: $(MKNLTSKDIR)\mdly_dsp.c $(INCS)
$(OBJSDIR)\msrh_top.obj: $(MKNLTSKDIR)\msrh_top.c $(INCS)
$(OBJSDIR)\mras_tex.obj: $(MKNLTSKDIR)\mras_tex.c $(INCS)
$(OBJSDIR)\mexe_tex.obj: $(MKNLTSKDIR)\mexe_tex.c $(INCS)

# μカーネル タスクキュー管理
$(OBJSDIR)\madd_que.obj: $(MKNLQUEDIR)\madd_que.c $(INCS)
$(OBJSDIR)\madf_que.obj: $(MKNLQUEDIR)\madf_que.c $(INCS)
$(OBJSDIR)\madp_que.obj: $(MKNLQUEDIR)\madp_que.c $(INCS)
$(OBJSDIR)\mrmv_que.obj: $(MKNLQUEDIR)\mrmv_que.c $(INCS)
$(OBJSDIR)\mrot_que.obj: $(MKNLQUEDIR)\mrot_que.c $(INCS)
$(OBJSDIR)\mclr_que.obj: $(MKNLQUEDIR)\mclr_que.c $(INCS)

# μカーネル タイムアウトキュー管理
$(OBJSDIR)\mtic_tmo.obj: $(MKNLTMODIR)\mtic_tmo.c $(INCS)
$(OBJSDIR)\madd_tmo.obj: $(MKNLTMODIR)\madd_tmo.c $(INCS)
$(OBJSDIR)\mrmv_tmo.obj: $(MKNLTMODIR)\mrmv_tmo.c $(INCS)

# HOS 固有
$(OBJSDIR)\sta_hos.obj: $(KNLHOSDIR)\sta_hos.c $(INCS)

# カーネルメモリ管理
$(OBJSDIR)\ini_mem.obj: $(KNLMEMDIR)\ini_mem.c $(INCS)
$(OBJSDIR)\alc_mem.obj: $(KNLMEMDIR)\alc_mem.c $(INCS)
$(OBJSDIR)\fre_mem.obj: $(KNLMEMDIR)\fre_mem.c $(INCS)

# タスク
$(OBJSDIR)\ini_tsk.obj: $(KNLTSKDIR)\ini_tsk.c $(INCS)
$(OBJSDIR)\cre_tsk.obj: $(KNLTSKDIR)\cre_tsk.c $(INCS)
$(OBJSDIR)\acre_tsk.obj: $(KNLTSKDIR)\acre_tsk.c $(INCS)
$(OBJSDIR)\kcre_tsk.obj: $(KNLTSKDIR)\kcre_tsk.c $(INCS)
$(OBJSDIR)\del_tsk.obj: $(KNLTSKDIR)\del_tsk.c $(INCS)
$(OBJSDIR)\act_tsk.obj: $(KNLTSKDIR)\act_tsk.c $(INCS)
$(OBJSDIR)\can_act.obj: $(KNLTSKDIR)\can_act.c $(INCS)
$(OBJSDIR)\sta_tsk.obj: $(KNLTSKDIR)\sta_tsk.c $(INCS)
$(OBJSDIR)\ext_tsk.obj: $(KNLTSKDIR)\ext_tsk.c $(INCS)
$(OBJSDIR)\exd_tsk.obj: $(KNLTSKDIR)\exd_tsk.c $(INCS)
$(OBJSDIR)\ter_tsk.obj: $(KNLTSKDIR)\ter_tsk.c $(INCS)
$(OBJSDIR)\chg_pri.obj: $(KNLTSKDIR)\chg_pri.c $(INCS)
$(OBJSDIR)\get_pri.obj: $(KNLTSKDIR)\get_pri.c $(INCS)
$(OBJSDIR)\ref_tst.obj: $(KNLTSKDIR)\ref_tst.c $(INCS)
$(OBJSDIR)\slp_tsk.obj: $(KNLTSKDIR)\slp_tsk.c $(INCS)
$(OBJSDIR)\tslp_tsk.obj: $(KNLTSKDIR)\tslp_tsk.c $(INCS)
$(OBJSDIR)\wup_tsk.obj: $(KNLTSKDIR)\wup_tsk.c $(INCS)
$(OBJSDIR)\can_wup.obj: $(KNLTSKDIR)\can_wup.c $(INCS)
$(OBJSDIR)\rel_wai.obj: $(KNLTSKDIR)\rel_wai.c $(INCS)
$(OBJSDIR)\sus_tsk.obj: $(KNLTSKDIR)\sus_tsk.c $(INCS)
$(OBJSDIR)\rsm_tsk.obj: $(KNLTSKDIR)\rsm_tsk.c $(INCS)
$(OBJSDIR)\frsm_tsk.obj: $(KNLTSKDIR)\frsm_tsk.c $(INCS)
$(OBJSDIR)\dly_tsk.obj: $(KNLTSKDIR)\dly_tsk.c $(INCS)
$(OBJSDIR)\ras_tex.obj: $(KNLTSKDIR)\ras_tex.c $(INCS)
$(OBJSDIR)\ktex_ent.obj: $(KNLTSKDIR)\ktex_ent.c $(INCS)
$(OBJSDIR)\dis_tex.obj: $(KNLTSKDIR)\dis_tex.c $(INCS)
$(OBJSDIR)\ena_tex.obj: $(KNLTSKDIR)\ena_tex.c $(INCS)
$(OBJSDIR)\sns_tex.obj: $(KNLTSKDIR)\sns_tex.c $(INCS)

# セマフォ
$(OBJSDIR)\ini_sem.obj: $(KNLSEMDIR)\ini_sem.c $(INCS)
$(OBJSDIR)\cre_sem.obj: $(KNLSEMDIR)\cre_sem.c $(INCS)
$(OBJSDIR)\acre_sem.obj: $(KNLSEMDIR)\acre_sem.c $(INCS)
$(OBJSDIR)\kcre_sem.obj: $(KNLSEMDIR)\kcre_sem.c $(INCS)
$(OBJSDIR)\del_sem.obj: $(KNLSEMDIR)\del_sem.c $(INCS)
$(OBJSDIR)\sig_sem.obj: $(KNLSEMDIR)\sig_sem.c $(INCS)
$(OBJSDIR)\wai_sem.obj: $(KNLSEMDIR)\wai_sem.c $(INCS)
$(OBJSDIR)\pol_sem.obj: $(KNLSEMDIR)\pol_sem.c $(INCS)
$(OBJSDIR)\twai_sem.obj: $(KNLSEMDIR)\twai_sem.c $(INCS)
$(OBJSDIR)\ref_sem.obj: $(KNLSEMDIR)\ref_sem.c $(INCS)

# イベントフラグ
$(OBJSDIR)\ini_flg.obj: $(KNLFLGDIR)\ini_flg.c $(INCS)
$(OBJSDIR)\cre_flg.obj: $(KNLFLGDIR)\cre_flg.c $(INCS)
$(OBJSDIR)\acre_flg.obj: $(KNLFLGDIR)\acre_flg.c $(INCS)
$(OBJSDIR)\kcre_flg.obj: $(KNLFLGDIR)\kcre_flg.c $(INCS)
$(OBJSDIR)\del_flg.obj: $(KNLFLGDIR)\del_flg.c $(INCS)
$(OBJSDIR)\set_flg.obj: $(KNLFLGDIR)\set_flg.c $(INCS)
$(OBJSDIR)\clr_flg.obj: $(KNLFLGDIR)\clr_flg.c $(INCS)
$(OBJSDIR)\wai_flg.obj: $(KNLFLGDIR)\wai_flg.c $(INCS)
$(OBJSDIR)\pol_flg.obj: $(KNLFLGDIR)\pol_flg.c $(INCS)
$(OBJSDIR)\twai_flg.obj: $(KNLFLGDIR)\twai_flg.c $(INCS)
$(OBJSDIR)\chk_flg.obj: $(KNLFLGDIR)\chk_flg.c $(INCS)
$(OBJSDIR)\ref_flg.obj: $(KNLFLGDIR)\ref_flg.c $(INCS)

# データキュー
$(OBJSDIR)\cre_dtq.obj: $(KNLDTQDIR)\cre_dtq.c $(INCS)
$(OBJSDIR)\acre_dtq.obj: $(KNLDTQDIR)\acre_dtq.c $(INCS)
$(OBJSDIR)\kcre_dtq.obj: $(KNLDTQDIR)\kcre_dtq.c $(INCS)
$(OBJSDIR)\del_dtq.obj: $(KNLDTQDIR)\del_dtq.c $(INCS)
$(OBJSDIR)\snd_dtq.obj: $(KNLDTQDIR)\snd_dtq.c $(INCS)
$(OBJSDIR)\psnd_dtq.obj: $(KNLDTQDIR)\psnd_dtq.c $(INCS)
$(OBJSDIR)\tsnd_dtq.obj: $(KNLDTQDIR)\tsnd_dtq.c $(INCS)
$(OBJSDIR)\fsnd_dtq.obj: $(KNLDTQDIR)\fsnd_dtq.c $(INCS)
$(OBJSDIR)\rcv_dtq.obj: $(KNLDTQDIR)\rcv_dtq.c $(INCS)
$(OBJSDIR)\prcv_dtq.obj: $(KNLDTQDIR)\prcv_dtq.c $(INCS)
$(OBJSDIR)\trcv_dtq.obj: $(KNLDTQDIR)\trcv_dtq.c $(INCS)
$(OBJSDIR)\ref_dtq.obj: $(KNLDTQDIR)\ref_dtq.c $(INCS)

# メールボックス
$(OBJSDIR)\cre_mbx.obj: $(KNLMBXDIR)\cre_mbx.c $(INCS)
$(OBJSDIR)\acre_mbx.obj: $(KNLMBXDIR)\acre_mbx.c $(INCS)
$(OBJSDIR)\kcre_mbx.obj: $(KNLMBXDIR)\kcre_mbx.c $(INCS)
$(OBJSDIR)\del_mbx.obj: $(KNLMBXDIR)\del_mbx.c $(INCS)
$(OBJSDIR)\snd_mbx.obj: $(KNLMBXDIR)\snd_mbx.c $(INCS)
$(OBJSDIR)\rcv_mbx.obj: $(KNLMBXDIR)\rcv_mbx.c $(INCS)
$(OBJSDIR)\prcv_mbx.obj: $(KNLMBXDIR)\prcv_mbx.c $(INCS)
$(OBJSDIR)\trcv_mbx.obj: $(KNLMBXDIR)\trcv_mbx.c $(INCS)
$(OBJSDIR)\ref_mbx.obj: $(KNLMBXDIR)\ref_mbx.c $(INCS)

# メッセージバッファ
$(OBJSDIR)\ini_mbf.obj: $(KNLMBFDIR)\ini_mbf.c $(INCS)
$(OBJSDIR)\cre_mbf.obj: $(KNLMBFDIR)\cre_mbf.c $(INCS)
$(OBJSDIR)\acre_mbf.obj: $(KNLMBFDIR)\acre_mbf.c $(INCS)
$(OBJSDIR)\kcre_mbf.obj: $(KNLMBFDIR)\kcre_mbf.c $(INCS)
$(OBJSDIR)\del_mbf.obj: $(KNLMBFDIR)\del_mbf.c $(INCS)
$(OBJSDIR)\snd_mbf.obj: $(KNLMBFDIR)\snd_mbf.c $(INCS)
$(OBJSDIR)\psnd_mbf.obj: $(KNLMBFDIR)\psnd_mbf.c $(INCS)
$(OBJSDIR)\tsnd_mbf.obj: $(KNLMBFDIR)\tsnd_mbf.c $(INCS)
$(OBJSDIR)\ksnd_mbf.obj: $(KNLMBFDIR)\ksnd_mbf.c $(INCS)
$(OBJSDIR)\rcv_mbf.obj: $(KNLMBFDIR)\rcv_mbf.c $(INCS)
$(OBJSDIR)\prcv_mbf.obj: $(KNLMBFDIR)\prcv_mbf.c $(INCS)
$(OBJSDIR)\trcv_mbf.obj: $(KNLMBFDIR)\trcv_mbf.c $(INCS)
$(OBJSDIR)\krcv_mbf.obj: $(KNLMBFDIR)\krcv_mbf.c $(INCS)
$(OBJSDIR)\ref_mbf.obj: $(KNLMBFDIR)\ref_mbf.c $(INCS)

# 固定長メモリプール
$(OBJSDIR)\ini_mpf.obj: $(KNLMPFDIR)\ini_mpf.c $(INCS)
$(OBJSDIR)\cre_mpf.obj: $(KNLMPFDIR)\cre_mpf.c $(INCS)
$(OBJSDIR)\acre_mpf.obj: $(KNLMPFDIR)\acre_mpf.c $(INCS)
$(OBJSDIR)\kcre_mpf.obj: $(KNLMPFDIR)\kcre_mpf.c $(INCS)
$(OBJSDIR)\del_mpf.obj: $(KNLMPFDIR)\del_mpf.c $(INCS)
$(OBJSDIR)\get_mpf.obj: $(KNLMPFDIR)\get_mpf.c $(INCS)
$(OBJSDIR)\pget_mpf.obj: $(KNLMPFDIR)\pget_mpf.c $(INCS)
$(OBJSDIR)\tget_mpf.obj: $(KNLMPFDIR)\tget_mpf.c $(INCS)
$(OBJSDIR)\rel_mpf.obj: $(KNLMPFDIR)\rel_mpf.c $(INCS)
$(OBJSDIR)\ref_mpf.obj: $(KNLMPFDIR)\ref_mpf.c $(INCS)

# 時間管理
$(OBJSDIR)\ini_tim.obj: $(KNLTIMDIR)\ini_tim.c $(INCS)
$(OBJSDIR)\set_tim.obj: $(KNLTIMDIR)\set_tim.c $(INCS)
$(OBJSDIR)\get_tim.obj: $(KNLTIMDIR)\get_tim.c $(INCS)
$(OBJSDIR)\isig_tim.obj: $(KNLTIMDIR)\isig_tim.c $(INCS)
$(OBJSDIR)\add_tml.obj: $(KNLTIMDIR)\add_tml.c $(INCS)
$(OBJSDIR)\rmv_tml.obj: $(KNLTIMDIR)\rmv_tml.c $(INCS)

# 周期ハンドラ
$(OBJSDIR)\ini_cyc.obj: $(KNLCYCDIR)\ini_cyc.c $(INCS)
$(OBJSDIR)\cyc_hdr.obj: $(KNLCYCDIR)\cyc_hdr.c $(INCS)
$(OBJSDIR)\sta_cyc.obj: $(KNLCYCDIR)\sta_cyc.c $(INCS)
$(OBJSDIR)\stp_cyc.obj: $(KNLCYCDIR)\stp_cyc.c $(INCS)
$(OBJSDIR)\cre_cyc.obj: $(KNLCYCDIR)\cre_cyc.c $(INCS)
$(OBJSDIR)\acre_cyc.obj: $(KNLCYCDIR)\acre_cyc.c $(INCS)
$(OBJSDIR)\kcre_cyc.obj: $(KNLCYCDIR)\kcre_cyc.c $(INCS)
$(OBJSDIR)\del_cyc.obj: $(KNLCYCDIR)\del_cyc.c $(INCS)

# アラームハンドラ
$(OBJSDIR)\ini_alm.obj: $(KNLALMDIR)\ini_alm.c $(INCS)
$(OBJSDIR)\alm_hdr.obj: $(KNLALMDIR)\alm_hdr.c $(INCS)
$(OBJSDIR)\sta_alm.obj: $(KNLALMDIR)\sta_alm.c $(INCS)
$(OBJSDIR)\stp_alm.obj: $(KNLALMDIR)\stp_alm.c $(INCS)

# 割り込み管理
$(OBJSDIR)\ram_int.obj: $(KNLINTDIR)\ram_int.c $(INCS)
$(OBJSDIR)\exe_int.obj: $(KNLINTDIR)\exe_int.c $(INCS)

# システム状態管理
$(OBJSDIR)\get_tid.obj: $(KNLSYSDIR)\get_tid.c $(INCS)
$(OBJSDIR)\kget_tid.obj: $(KNLSYSDIR)\kget_tid.c $(INCS)
$(OBJSDIR)\rot_rdq.obj: $(KNLSYSDIR)\rot_rdq.c $(INCS)
$(OBJSDIR)\loc_cpu.obj: $(KNLSYSDIR)\loc_cpu.c $(INCS)
$(OBJSDIR)\unl_cpu.obj: $(KNLSYSDIR)\unl_cpu.c $(INCS)
$(OBJSDIR)\dis_dsp.obj: $(KNLSYSDIR)\dis_dsp.c $(INCS)
$(OBJSDIR)\ena_dsp.obj: $(KNLSYSDIR)\ena_dsp.c $(INCS)
$(OBJSDIR)\sns_ctx.obj: $(KNLSYSDIR)\sns_ctx.c $(INCS)
$(OBJSDIR)\sns_loc.obj: $(KNLSYSDIR)\sns_loc.c $(INCS)
$(OBJSDIR)\sns_dsp.obj: $(KNLSYSDIR)\sns_dsp.c $(INCS)
$(OBJSDIR)\sns_dpn.obj: $(KNLSYSDIR)\sns_dpn.c $(INCS)
$(OBJSDIR)\ref_ver.obj: $(KNLSYSDIR)\ref_ver.c $(INCS)


.c.obj:
	$(CC) $(CFLAGS) -o$@ $<

clean:
	-del   $(OBJS)
	-rmdir $(OBJSDIR)
	-del   $(TARGET)
	-del   *.tds


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2003 by Project HOS                                      
# -----------------------------------------------------------------------------
