# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   ライブラリメイクファイル ARM SDT用                                         
#   ARMモード リトルエンディアン                                               
#                                                                              
#                                   Copyright (C) 1998-2002 by Ryuji Fuchikami 
# -----------------------------------------------------------------------------


# メイクプログラムに極力依存しないように、単純に記述しています。
# 動作確認は armmake.exe にて行っております。


# インクルードパス
INCDIR     = ..\..\include
INCPACDIR  = $(INCDIR)\arm

# ソースパス
PACDIR     = ..\..\src\arm
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
CC   = armcc
ASM  = armasm
LIBR = armlib

# オプション
CFLAGS = -c -I$(INCDIR) -I$(INCPACDIR)
AFLAGS = 
LFLAGS = 

# ターゲット
TARGET  = h4al.aof

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
OBJS = hospac.o inthdr.o irqhdr.o fiqhdr.o \
       mknlsys.o mknlint.o mknltsk.o mknlque.o mknltout.o \
       sta_hos.o ini_mem.o alc_mem.o fre_mem.o \
       ini_tsk.o cre_tsk.o acre_tsk.o act_tsk.o can_act.o \
       sta_tsk.o ext_tsk.o ter_tsk.o chg_pri.o get_pri.o \
       ref_tst.o \
       slp_tsk.o tslp_tsk.o wup_tsk.o can_wup.o rel_wai.o \
       sus_tsk.o rsm_tsk.o frsm_tsk.o dly_tsk.o \
       ini_sem.o sig_sem.o wai_sem.o pol_sem.o twai_sem.o \
       ini_flg.o set_flg.o clr_flg.o wai_flg.o pol_flg.o \
       twai_flg.o chk_flg.o \
       snd_dtq.o psnd_dtq.o rcv_dtq.o snd_mbx.o rcv_mbx.o \
       set_tim.o get_tim.o isig_tim.o sta_cyc.o stp_cyc.o \
       get_tid.o loc_cpu.o unl_cpu.o dis_dsp.o ena_dsp.o \
       sns_ctx.o sns_loc.o sns_dsp.o sns_dpn.o exe_int.o



# ライブラリ生成
$(TARGET): $(OBJS)
	$(LIBR) -c $(TARGET) $(OBJS)
	del	*.o


# プロセッサ依存
hospac.o: $(PACDIR)\hospac.s $(INCS)
	$(ASM) $(AFLAGS) $(PACDIR)\hospac.s

inthdr.o: $(PACDIR)\inthdr.s $(INCS)
	$(ASM) $(AFLAGS) $(PACDIR)\inthdr.s

irqhdr.o: $(PACDIR)\irqhdr.s $(INCS)
	$(ASM) $(AFLAGS) $(PACDIR)\irqhdr.s

fiqhdr.o: $(PACDIR)\fiqhdr.s $(INCS)
	$(ASM) $(AFLAGS) $(PACDIR)\fiqhdr.s


# μカーネル
mknlsys.o: $(MKNLDIR)\mknlsys.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlsys.c

mknlint.o: $(MKNLDIR)\mknlint.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlint.c

mknltsk.o: $(MKNLDIR)\mknltsk.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknltsk.c

mknlque.o: $(MKNLDIR)\mknlque.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknlque.c

mknltout.o: $(MKNLDIR)\mknltout.c $(INCS)
	$(CC) $(CFLAGS) $(MKNLDIR)\mknltout.c


# カーネル独自
sta_hos.o: $(KNLHOSDIR)\sta_hos.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\sta_hos.c

ini_mem.o: $(KNLHOSDIR)\ini_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\ini_mem.c

alc_mem.o: $(KNLHOSDIR)\alc_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\alc_mem.c

fre_mem.o: $(KNLHOSDIR)\fre_mem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLHOSDIR)\fre_mem.c 


# タスク
ini_tsk.o: $(KNLTSKDIR)\ini_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ini_tsk.c

cre_tsk.o: $(KNLTSKDIR)\cre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\cre_tsk.c

acre_tsk.o: $(KNLTSKDIR)\acre_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\acre_tsk.c

act_tsk.o: $(KNLTSKDIR)\act_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\act_tsk.c

can_act.o: $(KNLTSKDIR)\can_act.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\can_act.c

sta_tsk.o: $(KNLTSKDIR)\sta_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sta_tsk.c

ext_tsk.o: $(KNLTSKDIR)\ext_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ext_tsk.c

ter_tsk.o: $(KNLTSKDIR)\ter_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ter_tsk.c

chg_pri.o: $(KNLTSKDIR)\chg_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\chg_pri.c

get_pri.o: $(KNLTSKDIR)\get_pri.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\get_pri.c

ref_tst.o: $(KNLTSKDIR)\ref_tst.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\ref_tst.c

slp_tsk.o: $(KNLTSKDIR)\slp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\slp_tsk.c

tslp_tsk.o: $(KNLTSKDIR)\tslp_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\tslp_tsk.c

wup_tsk.o: $(KNLTSKDIR)\wup_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\wup_tsk.c

can_wup.o: $(KNLTSKDIR)\can_wup.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\can_wup.c

rel_wai.o: $(KNLTSKDIR)\rel_wai.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\rel_wai.c

sus_tsk.o: $(KNLTSKDIR)\sus_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\sus_tsk.c

rsm_tsk.o: $(KNLTSKDIR)\rsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\rsm_tsk.c

frsm_tsk.o: $(KNLTSKDIR)\frsm_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\frsm_tsk.c

dly_tsk.o: $(KNLTSKDIR)\dly_tsk.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTSKDIR)\dly_tsk.c


# セマフォ
ini_sem.o: $(KNLSEMDIR)\ini_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\ini_sem.c

sig_sem.o: $(KNLSEMDIR)\sig_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\sig_sem.c

wai_sem.o: $(KNLSEMDIR)\wai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\wai_sem.c

pol_sem.o: $(KNLSEMDIR)\pol_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\pol_sem.c

twai_sem.o: $(KNLSEMDIR)\twai_sem.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSEMDIR)\twai_sem.c


# イベントフラグ
ini_flg.o: $(KNLFLGDIR)\ini_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\ini_flg.c

set_flg.o: $(KNLFLGDIR)\set_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\set_flg.c

clr_flg.o: $(KNLFLGDIR)\clr_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\clr_flg.c

wai_flg.o: $(KNLFLGDIR)\wai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\wai_flg.c

pol_flg.o: $(KNLFLGDIR)\pol_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\pol_flg.c

twai_flg.o: $(KNLFLGDIR)\twai_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\twai_flg.c

chk_flg.o: $(KNLFLGDIR)\chk_flg.c $(INCS)
	$(CC) $(CFLAGS) $(KNLFLGDIR)\chk_flg.c


# データキュー
snd_dtq.o: $(KNLDTQDIR)\snd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\snd_dtq.c

psnd_dtq.o: $(KNLDTQDIR)\psnd_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\psnd_dtq.c

rcv_dtq.o: $(KNLDTQDIR)\rcv_dtq.c $(INCS)
	$(CC) $(CFLAGS) $(KNLDTQDIR)\rcv_dtq.c


# メールボックス
snd_mbx.o: $(KNLMBXDIR)\snd_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\snd_mbx.c

rcv_mbx.o: $(KNLMBXDIR)\rcv_mbx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLMBXDIR)\rcv_mbx.c


# 時間管理
set_tim.o: $(KNLTIMDIR)\set_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\set_tim.c

get_tim.o: $(KNLTIMDIR)\get_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\get_tim.c

isig_tim.o: $(KNLTIMDIR)\isig_tim.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\isig_tim.c

sta_cyc.o: $(KNLTIMDIR)\sta_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\sta_cyc.c

stp_cyc.o: $(KNLTIMDIR)\stp_cyc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLTIMDIR)\stp_cyc.c


# システム状態管理
get_tid.o: $(KNLSYSDIR)\get_tid.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\get_tid.c

loc_cpu.o: $(KNLSYSDIR)\loc_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\loc_cpu.c

unl_cpu.o: $(KNLSYSDIR)\unl_cpu.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\unl_cpu.c

dis_dsp.o: $(KNLSYSDIR)\dis_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\dis_dsp.c

ena_dsp.o: $(KNLSYSDIR)\ena_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\ena_dsp.c

sns_ctx.o: $(KNLSYSDIR)\sns_ctx.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_ctx.c

sns_loc.o: $(KNLSYSDIR)\sns_loc.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_loc.c

sns_dsp.o: $(KNLSYSDIR)\sns_dsp.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_dsp.c

sns_dpn.o: $(KNLSYSDIR)\sns_dpn.c $(INCS)
	$(CC) $(CFLAGS) $(KNLSYSDIR)\sns_dpn.c

exe_int.o: $(KNLINTDIR)\exe_int.c $(INCS)
	$(CC) $(CFLAGS) $(KNLINTDIR)\exe_int.c


clean:
	del	*.o
	del	$(TARGET)


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Ryuji Fuchikami                                  
# -----------------------------------------------------------------------------
