# Microsoft Visual C++ generated build script - Do not modify

PROJ = CHESS
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\MSVCPR~1\CHESS\COPYOF~2\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"CHESS.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:32767 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:32767 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = lafxcwd oldnames libw llibcew commdlg.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = CHESS.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		CHESS.SBR \
		MAINFRM.SBR \
		CHESSDOC.SBR \
		CHESSVW.SBR \
		RULES.SBR \
		STATSDLG.SBR \
		THINK.SBR


CHESS_RCDEP = d:\msvcpr~1\chess\copyof~2\res\chess.ico \
	d:\msvcpr~1\chess\copyof~2\res\bitmap1.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bitmap2.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bitmap3.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bitmap4.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bitmap5.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bitmap6.bmp \
	d:\msvcpr~1\chess\copyof~2\res\wbishop1.bmp \
	d:\msvcpr~1\chess\copyof~2\res\wking1.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bknight.bmp \
	d:\msvcpr~1\chess\copyof~2\res\wpawn1.bmp \
	d:\msvcpr~1\chess\copyof~2\res\bqueen.bmp \
	d:\msvcpr~1\chess\copyof~2\res\brook.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mpawn.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mbishop.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mking.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mknight.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mqueen.bmp \
	d:\msvcpr~1\chess\copyof~2\res\mrook.bmp \
	d:\msvcpr~1\chess\copyof~2\res\chess.rc2


STDAFX_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h


CHESS_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\mainfrm.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\chessvw.h


MAINFRM_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\mainfrm.h


CHESSDOC_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\rules.h \
	d:\msvcpr~1\chess\copyof~2\statsdlg.h


CHESSVW_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\chessvw.h \
	d:\msvcpr~1\chess\copyof~2\mainfrm.h \
	d:\msvcpr~1\chess\copyof~2\rules.h


RULES_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\rules.h


STATSDLG_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\statsdlg.h


THINK_DEP = d:\msvcpr~1\chess\copyof~2\stdafx.h \
	d:\msvcpr~1\chess\copyof~2\chess.h \
	d:\msvcpr~1\chess\copyof~2\chessdoc.h \
	d:\msvcpr~1\chess\copyof~2\rules.h


all:	$(PROJ).EXE $(PROJ).BSC

CHESS.RES:	CHESS.RC $(CHESS_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r CHESS.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CHESS.OBJ:	CHESS.CPP $(CHESS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHESS.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CHESSDOC.OBJ:	CHESSDOC.CPP $(CHESSDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHESSDOC.CPP

CHESSVW.OBJ:	CHESSVW.CPP $(CHESSVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHESSVW.CPP

RULES.OBJ:	RULES.CPP $(RULES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RULES.CPP

STATSDLG.OBJ:	STATSDLG.CPP $(STATSDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STATSDLG.CPP

THINK.OBJ:	THINK.CPP $(THINK_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c THINK.CPP


$(PROJ).EXE::	CHESS.RES

$(PROJ).EXE::	STDAFX.OBJ CHESS.OBJ MAINFRM.OBJ CHESSDOC.OBJ CHESSVW.OBJ RULES.OBJ \
	STATSDLG.OBJ THINK.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CHESS.OBJ +
MAINFRM.OBJ +
CHESSDOC.OBJ +
CHESSVW.OBJ +
RULES.OBJ +
STATSDLG.OBJ +
THINK.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) CHESS.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	CHESS.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) CHESS.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
