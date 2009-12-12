# Microsoft Developer Studio Project File - Name="UOS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=UOS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UOS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UOS.mak" CFG="UOS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UOS - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "UOS - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UOS - Win32 Release"

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
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "UOS - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UOS - Win32 Release"
# Name "UOS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UOS"

# PROP Default_Filter ""
# Begin Group "PORT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\UOS\PORT\VC6.0\OS_Port.c
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\PORT\VC6.0\OS_Port.h
# End Source File
# End Group
# Begin Group "SRC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Cfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Core.c
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Core.h
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Ext.c
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Ext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Pub.c
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Pub.h
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Sem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\UOS\SRC\OS_Sem.h
# End Source File
# End Group
# End Group
# Begin Group "APP"

# PROP Default_Filter ""
# Begin Group "HUCK"

# PROP Default_Filter ""
# Begin Group "ENERGY"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\C\Energy.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\H\Energy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\C\Energy_Proto.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\H\Energy_Proto.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\C\Energy_Settle.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\H\Energy_Settle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\C\Energy_Task.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Energy\H\Energy_Task.h
# End Source File
# End Group
# Begin Group "CLOCK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Clock\C\Clock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Clock\H\Clock.h
# End Source File
# End Group
# Begin Group "CONTROL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Control\C\Power_Ctrl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Control\H\Power_Ctrl.h
# End Source File
# End Group
# Begin Group "EVENTDATA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\C\Event_Cumu.C
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\H\Event_Cumu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\C\Event_Proto.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\H\Event_Proto.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\C\Event_Separate.C
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\EventData\H\Event_Separate.h
# End Source File
# End Group
# Begin Group "LOADDATA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\LoadData\C\Load_Data.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\LoadData\H\Load_Data.h
# End Source File
# End Group
# Begin Group "LOWPOWER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\LowPower\C\Low_Power.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\LowPower\H\Low_Power.h
# End Source File
# End Group
# Begin Group "MONITOR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Monitor\C\Sys_Monitor.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Monitor\H\Sys_Monitor.h
# End Source File
# End Group
# Begin Group "PROTOCOL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\C\645_1997.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\H\645_1997.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\C\Authority.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\H\Authority.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\C\Data_Trans.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\H\Data_Trans.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Protocol\H\Proto_DI.h
# End Source File
# End Group
# Begin Group "STORAGE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\C\Data_Para.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\H\Data_Para.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\C\Def_Para.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\H\Def_Para.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\H\Mem_Cfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\C\Sys_Memory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Storage\H\Sys_Memory.h
# End Source File
# End Group
# Begin Group "VOLSTAT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\C\VolStat.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\H\VolStat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\C\VolStat_Proto.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\H\VolStat_Proto.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\C\VolStat_Settle.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\VolStat\H\VolStat_Settle.h
# End Source File
# End Group
# Begin Group "DEMAND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\C\Demand.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\H\Demand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\C\Demand_Proto.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\H\Demand_Proto.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\C\Demand_Settle.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Demand\H\Demand_Settle.h
# End Source File
# End Group
# Begin Group "FREEZE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Freeze\C\Freeze_Data.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Freeze\H\Freeze_Data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Freeze\C\Freeze_Proto.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\HUCK\Freeze\H\Freeze_Proto.h
# End Source File
# End Group
# End Group
# Begin Group "PUB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Includes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\C\Pub.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Pub.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\C\Pub_Debug.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Pub_Debug.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Pub_Err.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Pub_Sem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\C\Pub_Time.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\Pub\H\Pub_Time.h
# End Source File
# End Group
# Begin Group "CFG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\Cfg\H\Meter_Cfg.h
# End Source File
# End Group
# Begin Group "MAIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\Main\C\Main_Proc.c
# End Source File
# End Group
# Begin Group "TASK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APP\TASK\C\TaskProc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\APP\TASK\H\TaskProc.h
# End Source File
# End Group
# End Group
# Begin Group "HAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\HAL\C\HAL.c
# End Source File
# Begin Source File

SOURCE=..\..\..\HAL\H\HAL.h
# End Source File
# End Group
# Begin Group "TEST"

# PROP Default_Filter ""
# Begin Group "HUCK_T"

# PROP Default_Filter ""
# Begin Group "FUNC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Test_Sys_Memory.c
# End Source File
# End Group
# Begin Group "UNIT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\TEST\HUCK_T\C\Test_Data_Trans.c
# End Source File
# Begin Source File

SOURCE=..\..\..\TEST\HUCK_T\C\Test_Energy_Settle.c
# End Source File
# End Group
# End Group
# Begin Group "PUB_T"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\TEST\PUB_T\C\Test_Pub.c
# End Source File
# Begin Source File

SOURCE=..\..\..\TEST\PUB_T\H\Test_Pub.h
# End Source File
# Begin Source File

SOURCE=..\..\..\TEST\PUB_T\C\Test_Stub.c
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
