# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   ライブラリメイクファイル H8/300h 秋月Cコンパイラ用                         
#                                                                              
#                                   Copyright (C) 1998-2002 by Ryuji Fuchikami 
# -----------------------------------------------------------------------------



# ライブラリアンには http://www.vector.co.jp/soft/win95/prog/se098521.html
# にて公開されている 江藤 善一 氏 の lib38.exe を勝手ながら利用させて
# いただきました。
# 
# メイクファイルは、なるべくいろんな make が利用できるように極力原始的な
# 書き方をしております。
# 秋月 Cコンパイラのインストール環境に合わせてインクルードパスを設定して
# ご使用ください。

# 当方、WinNT と Win2000 での開発ですので、Win95/98 のDOS窓だとコマンド
# ラインの長さが問題となるかもしれません。
# (基本的には make コマンド依存だと思います。)


INCH8DIR   = \akih8c
INCDIR     = ..\..\include
INCPACDIR  = ..\..\include\h8

PACDIR     = ..\..\src\h8
MKNLDIR    = ..\..\src\mknl
KERNELDIR  = ..\..\src\kernel
KNLHOSDIR  = $(KERNELDIR)\hos
KNLTSKDIR  = $(KERNELDIR)\tsk
KNLSEMDIR  = $(KERNELDIR)\sem
KNLFLGDIR  = $(KERNELDIR)\flg
KNLDTQDIR  = $(KERNELDIR)\dtq
KNLMBXDIR  = $(KERNELDIR)\mbx
KNLTIMDIR  = $(KERNELDIR)\tim
KNLSYSDIR  = $(KERNELDIR)\sys
KNLINTDIR  = $(KERNELDIR)\int

# ツール
CC   = cc38h
ASM  = a38h
LIBR = lib38

# オプション
CFLAGS = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR),$(INCPACDIR)
AFLAGS = 
LFLAGS = 

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
       $(INCPACDIR)\hospac.h \

# オブジェクトファイル
OBJS = ini_tsk.obj cre_tsk.obj acre_tsk.obj act_tsk.obj can_act.obj \
       sta_tsk.obj ext_tsk.obj ter_tsk.obj chg_pri.obj get_pri.obj \
       ref_tst.obj \
       slp_tsk.obj tslp_tsk.obj wup_tsk.obj can_wup.obj rel_wai.obj \
       sus_tsk.obj rsm_tsk.obj frsm_tsk.obj dly_tsk.obj \
       ini_sem.obj sig_sem.obj wai_sem.obj pol_sem.obj twai_sem.obj \
       ini_flg.obj set_flg.obj clr_flg.obj wai_flg.obj pol_flg.obj \
       twai_flg.obj chk_flg.obj \
       snd_dtq.obj psnd_dtq.obj rcv_dtq.obj snd_mbx.obj rcv_mbx.obj \
       set_tim.obj get_tim.obj isig_tim.obj sta_cyc.obj stp_cyc.obj \
       get_tid.obj loc_cpu.obj unl_cpu.obj dis_dsp.obj ena_dsp.obj \
       sns_ctx.obj sns_loc.obj sns_dsp.obj sns_dpn.obj exe_int.obj \
       ini_mem.obj alc_mem.obj fre_mem.obj \
       mknlsys.obj mknltsk.obj mknlque.obj mknltout.obj sta_hos.obj \
       pacini.obj pacint.obj pacctx.obj chg_imsk.obj get_imsk.obj


# ターゲット
TARGET  = h4akih8.lib


all: $(TARGET) h4akih8v.obj


# ライブラリ
$(TARGET): $(OBJS)
	$(LIBR) $(TARGET) $(OBJS)


# ベクタテーブル
h4akih8v.obj: $(PACDIR)\h4akih8v.src
	$(ASM) $(AFLAGS) $(PACDIR)\h4akih8v.src
	move $(PACDIR)\h4akih8v.obj .


# プロセッサ依存
pacini.obj: $(PACDIR)\pacini.c
	$(CC) $(CFLAGS) $(PACDIR)\pacini.c

pacctx.obj: $(PACDIR)\pacctx.src
	$(ASM) $(AFLAGS) $(PACDIR)\pacctx.src
	move $(PACDIR)\pacctx.obj .

pacint.obj: $(PACDIR)\pacint.src
	$(ASM) $(AFLAGS) $(PACDIR)\pacint.src
	move $(PACDIR)\pacint.obj .

chg_imsk.obj: $(PACDIR)\chg_imsk.c
	$(CC) $(CFLAGS) $(PACDIR)\chg_imsk.c

get_imsk.obj: $(PACDIR)\get_imsk.c
	$(CC) $(CFLAGS) $(PACDIR)\get_imsk.c


# μカーネル
mknlsys.obj: $(MKNLDIR)\mknlsys.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlsys.c

mknlint.obj: $(MKNLDIR)\mknlint.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlint.c

mknltsk.obj: $(MKNLDIR)\mknltsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknltsk.c

mknlque.obj: $(MKNLDIR)\mknlque.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlque.c

mknltout.obj: $(MKNLDIR)\mknltout.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknltout.c


# カーネル独自
sta_hos.obj: $(KNLHOSDIR)\sta_hos.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\sta_hos.c

ini_mem.obj: $(KNLHOSDIR)\ini_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\ini_mem.c

alc_mem.obj: $(KNLHOSDIR)\alc_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\alc_mem.c

fre_mem.obj: $(KNLHOSDIR)\fre_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\fre_mem.c 


# タスク
ini_tsk.obj: $(KNLTSKDIR)\ini_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ini_tsk.c

cre_tsk.obj: $(KNLTSKDIR)\cre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\cre_tsk.c

acre_tsk.obj: $(KNLTSKDIR)\acre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\acre_tsk.c

act_tsk.obj: $(KNLTSKDIR)\act_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\act_tsk.c

can_act.obj: $(KNLTSKDIR)\can_act.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\can_act.c

sta_tsk.obj: $(KNLTSKDIR)\sta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sta_tsk.c

ext_tsk.obj: $(KNLTSKDIR)\ext_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ext_tsk.c

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


# セマフォ
ini_sem.obj: $(KNLSEMDIR)\ini_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\ini_sem.c

sig_sem.obj: $(KNLSEMDIR)\sig_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\sig_sem.c

wai_sem.obj: $(KNLSEMDIR)\wai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\wai_sem.c

pol_sem.obj: $(KNLSEMDIR)\pol_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\pol_sem.c

twai_sem.obj: $(KNLSEMDIR)\twai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\twai_sem.c


# イベントフラグ
ini_flg.obj: $(KNLFLGDIR)\ini_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\ini_flg.c

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


# データキュー
snd_dtq.obj: $(KNLDTQDIR)\snd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\snd_dtq.c

psnd_dtq.obj: $(KNLDTQDIR)\psnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\psnd_dtq.c

rcv_dtq.obj: $(KNLDTQDIR)\rcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\rcv_dtq.c


# メールボックス
snd_mbx.obj: $(KNLMBXDIR)\snd_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\snd_mbx.c

rcv_mbx.obj: $(KNLMBXDIR)\rcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\rcv_mbx.c


# 時間管理
set_tim.obj: $(KNLTIMDIR)\set_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\set_tim.c

get_tim.obj: $(KNLTIMDIR)\get_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\get_tim.c

isig_tim.obj: $(KNLTIMDIR)\isig_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\isig_tim.c

sta_cyc.obj: $(KNLTIMDIR)\sta_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\sta_cyc.c

stp_cyc.obj: $(KNLTIMDIR)\stp_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\stp_cyc.c


# システム状態管理
get_tid.obj: $(KNLSYSDIR)\get_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\get_tid.c

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

exe_int.obj: $(KNLINTDIR)\exe_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)\exe_int.c



clean:
	del *.obj


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Ryuji Fuchikami                                  
# -----------------------------------------------------------------------------
