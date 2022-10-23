# Microsoft Developer Studio Project File - Name="Usage Meter 3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Usage Meter 3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Usage Meter 3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Usage Meter 3.mak" CFG="Usage Meter 3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Usage Meter 3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Usage Meter 3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Usage Meter 3 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Wininet.lib /nologo /subsystem:windows /machine:I386 /out:"C:\Program Files\Usage Meter\UsageMeter3.exe"

!ELSEIF  "$(CFG)" == "Usage Meter 3 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Wininet.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/UM_Dbug300.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Usage Meter 3 - Win32 Release"
# Name "Usage Meter 3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MyBeepDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyClientPort.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDate.cpp
# End Source File
# Begin Source File

SOURCE=.\MyEventLog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLogFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLogPath.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMainWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\MyServerPort.cpp
# End Source File
# Begin Source File

SOURCE=.\MyString.cpp
# End Source File
# Begin Source File

SOURCE=.\MyUser.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\Usage Meter 3.cpp"
# End Source File
# Begin Source File

SOURCE=".\Usage Meter 3.rc"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MyBeepDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyClientPort.h
# End Source File
# Begin Source File

SOURCE=.\MyCounter.h
# End Source File
# Begin Source File

SOURCE=.\MyDate.h
# End Source File
# Begin Source File

SOURCE=.\MyEventLog.h
# End Source File
# Begin Source File

SOURCE=.\MyGlobal.h
# End Source File
# Begin Source File

SOURCE=.\MyListView.h
# End Source File
# Begin Source File

SOURCE=.\MyLogFile.h
# End Source File
# Begin Source File

SOURCE=.\MyLogPath.h
# End Source File
# Begin Source File

SOURCE=.\MyMainWnd.h
# End Source File
# Begin Source File

SOURCE=.\MyRegistry.h
# End Source File
# Begin Source File

SOURCE=.\MyServerPort.h
# End Source File
# Begin Source File

SOURCE=.\MyString.h
# End Source File
# Begin Source File

SOURCE=.\MyUser.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\Usage Meter 3.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\About.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource.h
# End Source File
# Begin Source File

SOURCE=.\res\Tip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tip.ico
# End Source File
# Begin Source File

SOURCE=".\res\Usage Meter 3.ico"
# End Source File
# Begin Source File

SOURCE=".\Usage Meter 3.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\XPStyle.manifest
# End Source File
# End Target
# End Project
