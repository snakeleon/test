# Project: 	main
# Compiler: Default MinGW compiler
# Compiler Type:  GCC 5
# Makefile created by SiFe on 2009-08-02 19:46

OS      	:= $(shell uname -o)
IS_LINUX 	:= $(shell echo $(OS) | grep -i Linux)
IS_MSYS  	:= $(shell echo $(OS) | grep -i Msys)
WHITHER 	= build

CXX       	= g++
CC        	= gcc
WINDRES   	= windres
OBJ       	= $(WHITHER)/main.o
LINKOBJ   	= $(WHITHER)/main.o
SOURSE    	= main.cpp
DEPENDENT 	= ncursesw
LIBS      	= `pkg-config --libs $(DEPENDENT)`
INCS      	= `pkg-config --cflags-only-I $(DEPENDENT)`
CXXINCS   	= `pkg-config --cflags-only-I $(DEPENDENT)`

ifdef IS_LINUX
	LC_OS	= "Current OS is Linux"
	BIN 	= $(WHITHER)/main
else
	ifdef IS_MSYS
	LC_OS 	= "Current OS is MSYS"
	BIN		= $(WHITHER)/main.exe
endif
endif

DEFINES   =
CXXFLAGS  = $(CXXINCS) 	$(DEFINES) 	-O0 -Wall -Wextra -fexceptions \
                                    -Wfloat-equal -std=c++14
CFLAGS    = $(INCS) 	$(DEFINES) 	-O2 -Wall -Wextra -fexceptions \
                                    -Wfloat-equal
GPROF     = gprof
RM        = rm  -rf
LINK      = g++

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

checkos:
	@echo $(LC_OS)

clean: clean-custom
	$(RM) $(OBJ) $(BIN)


$(BIN): $(LINKOBJ)
	$(LINK) $(LINKOBJ) -o $(BIN) $(LIBS)

$(LINKOBJ): $(SOURSE)
	$(shell test -d $(WHITHER) || mkdir $(WHITHER))
	$(CXX) -c -g $(SOURSE) -o $(OBJ) $(CXXFLAGS)
