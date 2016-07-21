# Project: 	SDL_test
# Compiler: Default MinGW compiler
# Compiler Type:  GCC 5
# Makefile created by SiFe on 2009-08-02 19:46

OS      	:= $(shell uname -o)
IS_LINUX 	:= $(shell echo $(OS) | grep -i Linux)
IS_MSYS  	:= $(shell echo $(OS) | grep -i Msys)

CPP       	= g++
CC        	= gcc
WINDRES   	= windres
OBJ       	= SDL_test.o
LINKOBJ   	= SDL_test.o
SOURSE    	= SDL_test.cpp
DEPENDENT 	= SDL2_gfx SDL2_ttf sdl2
LIBS      	= `pkg-config --libs $(DEPENDENT)`
INCS      	= `pkg-config --cflags-only-I $(DEPENDENT)`
CXXINCS   	= `pkg-config --cflags-only-I $(DEPENDENT)`
WHITHER 	= build

ifdef IS_LINUX
LC_OS	= "Current OS is Linux"
BIN 	= SDL_test
else
ifdef IS_MSYS
LC_OS 	= "Current OS is MSYS"
BIN		= SDL_test.exe
endif
endif

DEFINES   =
CXXFLAGS  = $(CXXINCS) 	$(DEFINES) 	-O2 -Wall -Wextra -fexceptions \
                                    -Wfloat-equal -std=c++14
CFLAGS    = $(INCS) 	$(DEFINES) 	-O2 -Wall -Wextra -fexceptions \
                                    -Wfloat-equal
GPROF     = gprof
RM        = rm  -rf
LINK      = g++

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

checkos:
	echo $(LC_OS)

clean: clean-custom
	$(RM) $(WHITHER)/$(OBJ) $(WHITHER)/$(BIN)


$(BIN): $(LINKOBJ)
	$(LINK) $(WHITHER)/$(LINKOBJ) -o $(WHITHER)/$(BIN) $(LIBS)

$(LINKOBJ): $(SOURSE)
	$(shell test -d $(WHITHER) || mkdir $(WHITHER))
	$(CPP) -c $(SOURSE) -o $(WHITHER)/$(OBJ) $(CXXFLAGS)
