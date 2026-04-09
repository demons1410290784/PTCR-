# Microsoft Developer Studio Generated NMAKE File, Based on Ptcr.dsp
!IF "$(CFG)" == ""
CFG=Ptcr - Win32 Release
!MESSAGE No configuration specified. Defaulting to Ptcr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Ptcr - Win32 Release" && "$(CFG)" != "Ptcr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ptcr.mak" CFG="Ptcr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ptcr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ptcr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Ptcr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Ptcr.exe" "$(OUTDIR)\Ptcr.bsc"


CLEAN :
	-@erase "$(INTDIR)\CombinDlg.obj"
	-@erase "$(INTDIR)\CombinDlg.sbr"
	-@erase "$(INTDIR)\Comcfg.obj"
	-@erase "$(INTDIR)\Comcfg.sbr"
	-@erase "$(INTDIR)\Draw.obj"
	-@erase "$(INTDIR)\Draw.sbr"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\font.sbr"
	-@erase "$(INTDIR)\gridctrl.obj"
	-@erase "$(INTDIR)\gridctrl.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ManCmd1.obj"
	-@erase "$(INTDIR)\ManCmd1.sbr"
	-@erase "$(INTDIR)\NameResi.obj"
	-@erase "$(INTDIR)\NameResi.sbr"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\picture.sbr"
	-@erase "$(INTDIR)\Ptcr.obj"
	-@erase "$(INTDIR)\Ptcr.pch"
	-@erase "$(INTDIR)\Ptcr.res"
	-@erase "$(INTDIR)\Ptcr.sbr"
	-@erase "$(INTDIR)\PtcrDoc.obj"
	-@erase "$(INTDIR)\PtcrDoc.sbr"
	-@erase "$(INTDIR)\PtcrView.obj"
	-@erase "$(INTDIR)\PtcrView.sbr"
	-@erase "$(INTDIR)\RT.obj"
	-@erase "$(INTDIR)\RT.sbr"
	-@erase "$(INTDIR)\RTSave.obj"
	-@erase "$(INTDIR)\RTSave.sbr"
	-@erase "$(INTDIR)\SerialPort.obj"
	-@erase "$(INTDIR)\SerialPort.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Ptcr.bsc"
	-@erase "$(OUTDIR)\Ptcr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptcr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Ptcr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptcr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CombinDlg.sbr" \
	"$(INTDIR)\Comcfg.sbr" \
	"$(INTDIR)\Draw.sbr" \
	"$(INTDIR)\font.sbr" \
	"$(INTDIR)\gridctrl.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ManCmd1.sbr" \
	"$(INTDIR)\NameResi.sbr" \
	"$(INTDIR)\picture.sbr" \
	"$(INTDIR)\Ptcr.sbr" \
	"$(INTDIR)\PtcrDoc.sbr" \
	"$(INTDIR)\PtcrView.sbr" \
	"$(INTDIR)\RT.sbr" \
	"$(INTDIR)\RTSave.sbr" \
	"$(INTDIR)\SerialPort.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ptcr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Ptcr.pdb" /machine:I386 /out:"$(OUTDIR)\Ptcr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CombinDlg.obj" \
	"$(INTDIR)\Comcfg.obj" \
	"$(INTDIR)\Draw.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\gridctrl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ManCmd1.obj" \
	"$(INTDIR)\NameResi.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\Ptcr.obj" \
	"$(INTDIR)\PtcrDoc.obj" \
	"$(INTDIR)\PtcrView.obj" \
	"$(INTDIR)\RT.obj" \
	"$(INTDIR)\RTSave.obj" \
	"$(INTDIR)\SerialPort.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptcr.res"

"$(OUTDIR)\Ptcr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ptcr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Ptcr.exe" "$(OUTDIR)\Ptcr.bsc"


CLEAN :
	-@erase "$(INTDIR)\CombinDlg.obj"
	-@erase "$(INTDIR)\CombinDlg.sbr"
	-@erase "$(INTDIR)\Comcfg.obj"
	-@erase "$(INTDIR)\Comcfg.sbr"
	-@erase "$(INTDIR)\Draw.obj"
	-@erase "$(INTDIR)\Draw.sbr"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\font.sbr"
	-@erase "$(INTDIR)\gridctrl.obj"
	-@erase "$(INTDIR)\gridctrl.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ManCmd1.obj"
	-@erase "$(INTDIR)\ManCmd1.sbr"
	-@erase "$(INTDIR)\NameResi.obj"
	-@erase "$(INTDIR)\NameResi.sbr"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\picture.sbr"
	-@erase "$(INTDIR)\Ptcr.obj"
	-@erase "$(INTDIR)\Ptcr.pch"
	-@erase "$(INTDIR)\Ptcr.res"
	-@erase "$(INTDIR)\Ptcr.sbr"
	-@erase "$(INTDIR)\PtcrDoc.obj"
	-@erase "$(INTDIR)\PtcrDoc.sbr"
	-@erase "$(INTDIR)\PtcrView.obj"
	-@erase "$(INTDIR)\PtcrView.sbr"
	-@erase "$(INTDIR)\RT.obj"
	-@erase "$(INTDIR)\RT.sbr"
	-@erase "$(INTDIR)\RTSave.obj"
	-@erase "$(INTDIR)\RTSave.sbr"
	-@erase "$(INTDIR)\SerialPort.obj"
	-@erase "$(INTDIR)\SerialPort.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Ptcr.bsc"
	-@erase "$(OUTDIR)\Ptcr.exe"
	-@erase "$(OUTDIR)\Ptcr.ilk"
	-@erase "$(OUTDIR)\Ptcr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptcr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Ptcr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptcr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CombinDlg.sbr" \
	"$(INTDIR)\Comcfg.sbr" \
	"$(INTDIR)\Draw.sbr" \
	"$(INTDIR)\font.sbr" \
	"$(INTDIR)\gridctrl.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ManCmd1.sbr" \
	"$(INTDIR)\NameResi.sbr" \
	"$(INTDIR)\picture.sbr" \
	"$(INTDIR)\Ptcr.sbr" \
	"$(INTDIR)\PtcrDoc.sbr" \
	"$(INTDIR)\PtcrView.sbr" \
	"$(INTDIR)\RT.sbr" \
	"$(INTDIR)\RTSave.sbr" \
	"$(INTDIR)\SerialPort.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ptcr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Ptcr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Ptcr.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CombinDlg.obj" \
	"$(INTDIR)\Comcfg.obj" \
	"$(INTDIR)\Draw.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\gridctrl.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ManCmd1.obj" \
	"$(INTDIR)\NameResi.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\Ptcr.obj" \
	"$(INTDIR)\PtcrDoc.obj" \
	"$(INTDIR)\PtcrView.obj" \
	"$(INTDIR)\RT.obj" \
	"$(INTDIR)\RTSave.obj" \
	"$(INTDIR)\SerialPort.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptcr.res"

"$(OUTDIR)\Ptcr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Ptcr.dep")
!INCLUDE "Ptcr.dep"
!ELSE 
!MESSAGE Warning: cannot find "Ptcr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Ptcr - Win32 Release" || "$(CFG)" == "Ptcr - Win32 Debug"
SOURCE=.\CombinDlg.cpp

"$(INTDIR)\CombinDlg.obj"	"$(INTDIR)\CombinDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\Comcfg.cpp

"$(INTDIR)\Comcfg.obj"	"$(INTDIR)\Comcfg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\Draw.cpp

"$(INTDIR)\Draw.obj"	"$(INTDIR)\Draw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\font.cpp

"$(INTDIR)\font.obj"	"$(INTDIR)\font.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\gridctrl.cpp

"$(INTDIR)\gridctrl.obj"	"$(INTDIR)\gridctrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\ManCmd1.cpp

"$(INTDIR)\ManCmd1.obj"	"$(INTDIR)\ManCmd1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\NameResi.cpp

"$(INTDIR)\NameResi.obj"	"$(INTDIR)\NameResi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\picture.cpp

"$(INTDIR)\picture.obj"	"$(INTDIR)\picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\Ptcr.cpp

"$(INTDIR)\Ptcr.obj"	"$(INTDIR)\Ptcr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\Ptcr.rc

"$(INTDIR)\Ptcr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\PtcrDoc.cpp

"$(INTDIR)\PtcrDoc.obj"	"$(INTDIR)\PtcrDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\PtcrView.cpp

"$(INTDIR)\PtcrView.obj"	"$(INTDIR)\PtcrView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\RT.cpp

"$(INTDIR)\RT.obj"	"$(INTDIR)\RT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE=.\RTSave.cpp

"$(INTDIR)\RTSave.obj"	"$(INTDIR)\RTSave.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"


SOURCE="..\ptcrt-w\SerialPort.cpp"

"$(INTDIR)\SerialPort.obj"	"$(INTDIR)\SerialPort.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptcr.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Ptcr - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptcr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ptcr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptcr - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptcr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ptcr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

