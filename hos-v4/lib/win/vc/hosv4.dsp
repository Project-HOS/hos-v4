# Microsoft Developer Studio Project File - Name="hosv4" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=hosv4 - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "hosv4.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "hosv4.mak" CFG="hosv4 - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "hosv4 - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "hosv4 - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "hosv4 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\include" /I "..\..\..\include\win" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "hosv4 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\include\win" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "hosv4 - Win32 Release"
# Name "hosv4 - Win32 Debug"
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\include\dsp_hok.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\hosdenv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\hoserchk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\hoslib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\win\hospac.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\itron.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\kernel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_alm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_cyc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_dtq.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_exc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_flg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_hos.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_int.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_mbf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_mbx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_mpf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_sem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_sys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_tim.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\knl_tsk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\mknl.h
# End Source File
# End Group
# Begin Group "win"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\win\hospac.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\pacint.c
# End Source File
# End Group
# Begin Group "kernel"

# PROP Default_Filter ""
# Begin Group "hos"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\hos\sta_hos.c
# End Source File
# End Group
# Begin Group "tsk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\acre_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\act_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\can_act.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\can_wup.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\chg_pri.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\cre_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\del_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\dis_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\dly_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ena_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\exd_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ext_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\frsm_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\get_pri.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ini_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\kcre_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ktex_ent.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ras_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ref_tst.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\rel_wai.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\rsm_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\slp_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\sns_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\sta_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\sus_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\ter_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\tslp_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tsk\wup_tsk.c
# End Source File
# End Group
# Begin Group "sem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\acre_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\cre_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\del_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\ini_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\kcre_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\pol_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\ref_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\sig_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\twai_sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sem\wai_sem.c
# End Source File
# End Group
# Begin Group "flg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\acre_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\chk_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\clr_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\cre_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\del_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\ini_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\kcre_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\pol_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\ref_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\set_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\twai_flg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\flg\wai_flg.c
# End Source File
# End Group
# Begin Group "dtq"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\acre_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\cre_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\del_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\fsnd_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\kcre_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\prcv_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\psnd_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\rcv_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\ref_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\snd_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\trcv_dtq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\dtq\tsnd_dtq.c
# End Source File
# End Group
# Begin Group "sys"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\dis_dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\ena_dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\get_tid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\kget_tid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\loc_cpu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\ref_ver.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\sns_ctx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\sns_dpn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\sns_dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\sns_loc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\sys\unl_cpu.c
# End Source File
# End Group
# Begin Group "tim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\add_tml.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\get_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\ini_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\isig_tim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\rmv_tml.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\tim\set_tim.c
# End Source File
# End Group
# Begin Group "int"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\int\exe_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\int\ram_int.c
# End Source File
# End Group
# Begin Group "mbx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\acre_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\cre_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\del_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\kcre_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\prcv_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\rcv_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\ref_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\snd_mbx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbx\trcv_mbx.c
# End Source File
# End Group
# Begin Group "mpf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\acre_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\cre_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\del_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\get_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\ini_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\kcre_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\pget_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\ref_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\rel_mpf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mpf\tget_mpf.c
# End Source File
# End Group
# Begin Group "mem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\mem\alc_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mem\fre_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mem\ini_mem.c
# End Source File
# End Group
# Begin Group "mbf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\acre_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\cre_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\del_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\ini_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\kcre_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\krcv_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\ksnd_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\prcv_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\psnd_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\rcv_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\ref_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\snd_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\trcv_mbf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\mbf\tsnd_mbf.c
# End Source File
# End Group
# Begin Group "cyc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\cyc\cyc_hdr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\cyc\ini_cyc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\cyc\sta_cyc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\cyc\stp_cyc.c
# End Source File
# End Group
# Begin Group "alm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\kernel\alm\alm_hdr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\alm\ini_alm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\alm\sta_alm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\kernel\alm\stp_alm.c
# End Source File
# End Group
# End Group
# Begin Group "mknl"

# PROP Default_Filter ""
# Begin Group "mtsk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mchg_pri.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mdly_dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mexe_dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mexe_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mras_tex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mrot_rdq.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mrsm_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\msrh_top.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\msta_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\msus_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mter_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mwai_tsk.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tsk\mwup_tsk.c
# End Source File
# End Group
# Begin Group "msys"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\mknl\sys\mext_stu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\sys\midl_lop.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\sys\mini_sys.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\sys\msta_stu.c
# End Source File
# End Group
# Begin Group "mque"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\mknl\que\madd_que.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\que\madf_que.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\que\madp_que.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\que\mclr_que.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\que\mrmv_que.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\que\mrot_que.c
# End Source File
# End Group
# Begin Group "mtmout"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\mknl\tmout\madd_tmo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tmout\mrmv_tmo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mknl\tmout\mtic_tmo.c
# End Source File
# End Group
# End Group
# End Target
# End Project
