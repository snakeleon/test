# Project: 	Test
# Compiler: Default MinGW compiler
# Compiler Type:  GCC 4
# Makefile created by SiFe on 2009-08-02 19:46

CPP       = g++.exe
CC        = gcc.exe
WINDRES   = windres.exe
OBJ       = library.obj
LINKOBJ   = library.obj
SOURSE    = library.cpp
LIBS      = -L"D:/MSYS32/MinGW32/lib"
INCS      = -I"D:/MSYS32/MinGW32/include"
CXXINCS   = -I"D:/MSYS32/MinGW32/include" 
BIN       = library.exe
DEFINES   = 
CXXFLAGS  = $(CXXINCS) $(DEFINES) -O3 -g3 -Wall
CFLAGS    = $(INCS) $(DEFINES)	-O3 -g3 -Wall 
GPROF     = gprof.exe
RM        = rm  -rf
LINK      = g++.exe

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN)
	

$(BIN): $(LINKOBJ)
	$(LINK) $(LINKOBJ) -o $(BIN) $(LIBS)

$(LINKOBJ): $(SOURSE)
	$(CPP) -c $(SOURSE) -o $(OBJ) $(CXXFLAGS)
