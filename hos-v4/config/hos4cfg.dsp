# Microsoft Developer Studio Project File - Name="hos4cfg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=hos4cfg - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "hos4cfg.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "hos4cfg.mak" CFG="hos4cfg - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "hos4cfg - Win32 Release" ("Win32 (x86) Console Application" 用)
!MESSAGE "hos4cfg - Win32 Debug" ("Win32 (x86) Console Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/HOS/HOS_v4/config", MEAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "hos4cfg - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "hos4cfg - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "hos4cfg - Win32 Release"
# Name "hos4cfg - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\analyze.cpp
# End Source File
# Begin Source File

SOURCE=.\apidef.cpp
# End Source File
# Begin Source File

SOURCE=.\apiinc.cpp
# End Source File
# Begin Source File

SOURCE=.\attini.cpp
# End Source File
# Begin Source File

SOURCE=.\attisr.cpp
# End Source File
# Begin Source File

SOURCE=.\crecyc.cpp
# End Source File
# Begin Source File

SOURCE=.\credtq.cpp
# End Source File
# Begin Source File

SOURCE=.\creflg.cpp
# End Source File
# Begin Source File

SOURCE=.\crembf.cpp
# End Source File
# Begin Source File

SOURCE=.\crembx.cpp
# End Source File
# Begin Source File

SOURCE=.\crempf.cpp
# End Source File
# Begin Source File

SOURCE=.\cresem.cpp
# End Source File
# Begin Source File

SOURCE=.\cretsk.cpp
# End Source File
# Begin Source File

SOURCE=.\defercd.cpp
# End Source File
# Begin Source File

SOURCE=.\defexc.cpp
# End Source File
# Begin Source File

SOURCE=.\deftex.cpp
# End Source File
# Begin Source File

SOURCE=.\hos4cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\idlstk.cpp
# End Source File
# Begin Source File

SOURCE=.\intstk.cpp
# End Source File
# Begin Source File

SOURCE=.\knlheap.cpp
# End Source File
# Begin Source File

SOURCE=.\maxtpri.cpp
# End Source File
# Begin Source File

SOURCE=.\parpack.cpp
# End Source File
# Begin Source File

SOURCE=.\read.cpp
# End Source File
# Begin Source File

SOURCE=.\timtic.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\analyze.h
# End Source File
# Begin Source File

SOURCE=.\apidef.h
# End Source File
# Begin Source File

SOURCE=.\apiinc.h
# End Source File
# Begin Source File

SOURCE=.\attini.h
# End Source File
# Begin Source File

SOURCE=.\attisr.h
# End Source File
# Begin Source File

SOURCE=.\crecyc.h
# End Source File
# Begin Source File

SOURCE=.\credtq.h
# End Source File
# Begin Source File

SOURCE=.\creflg.h
# End Source File
# Begin Source File

SOURCE=.\crembf.h
# End Source File
# Begin Source File

SOURCE=.\crembx.h
# End Source File
# Begin Source File

SOURCE=.\crempf.h
# End Source File
# Begin Source File

SOURCE=.\cresem.h
# End Source File
# Begin Source File

SOURCE=.\cretsk.h
# End Source File
# Begin Source File

SOURCE=.\defercd.h
# End Source File
# Begin Source File

SOURCE=.\defexc.h
# End Source File
# Begin Source File

SOURCE=.\deftex.h
# End Source File
# Begin Source File

SOURCE=.\idlstk.h
# End Source File
# Begin Source File

SOURCE=.\intstk.h
# End Source File
# Begin Source File

SOURCE=.\knlheap.h
# End Source File
# Begin Source File

SOURCE=.\maxtpri.h
# End Source File
# Begin Source File

SOURCE=.\parpack.h
# End Source File
# Begin Source File

SOURCE=.\read.h
# End Source File
# Begin Source File

SOURCE=.\timtic.h
# End Source File
# End Group
# End Target
# End Project
