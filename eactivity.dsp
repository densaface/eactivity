# Microsoft Developer Studio Project File - Name="eactivity" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=eactivity - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "eactivity.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "eactivity.mak" CFG="eactivity - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "eactivity - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "eactivity - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "eactivity - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "eactivity - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "eactivity - Win32 Release"
# Name "eactivity - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ext_src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AppendHead.cpp
# End Source File
# Begin Source File

SOURCE=.\AppendHead.h
# End Source File
# Begin Source File

SOURCE=.\bmpext\bmpext.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpext\bmpext.h
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\CpuUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\CpuUsage.h
# End Source File
# Begin Source File

SOURCE=.\bmpext\ddbdrawex.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpext\dib.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpext\Dib2.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpext\Dib2.h
# End Source File
# Begin Source File

SOURCE=.\bmpext\Dib3.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpext\Dib3.h
# End Source File
# Begin Source File

SOURCE=.\Koeff.cpp
# End Source File
# Begin Source File

SOURCE=.\Koeff.h
# End Source File
# Begin Source File

SOURCE=.\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\ppToolTip\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=.\bmpext\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Trifle1.cpp
# End Source File
# Begin Source File

SOURCE=.\Trifle1.h
# End Source File
# Begin Source File

SOURCE=.\ViewRules.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewRules.h
# End Source File
# Begin Source File

SOURCE=.\WinWork.cpp
# End Source File
# Begin Source File

SOURCE=.\WinWork.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\eactivity.cpp
# End Source File
# Begin Source File

SOURCE=.\eactivity.rc
# End Source File
# Begin Source File

SOURCE=.\eactivityDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\eactivity.h
# End Source File
# Begin Source File

SOURCE=.\eactivityDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\eactivity.ico
# End Source File
# Begin Source File

SOURCE=.\res\eactivity.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
