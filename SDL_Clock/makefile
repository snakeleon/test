# Project: 	SDL_test
# Compiler: Default MinGW compiler
# Compiler Type:  GCC 5
# Makefile created by SiFe on 2009-08-02 19:46

CPP       = g++
CC        = gcc
WINDRES   = windres
OBJ       = SDL_test.o
LINKOBJ   = SDL_test.o
SOURSE    = SDL_test.cpp
DEPENDENT = SDL2_gfx SDL2_ttf sdl2
LIBS      = -L"D:/MSYS32/MinGW32/lib" `pkg-config --libs $(DEPENDENT)`
INCS      = -I"D:/MSYS32/MinGW32/include"
CXXINCS   = -I"D:/MSYS32/MinGW32/include"
BIN       = SDL_test
DEFINES   =
CXXFLAGS  = $(CXXINCS) $(DEFINES) -O2 -Wall -Wextra -std=c++11
CFLAGS    = $(INCS) $(DEFINES)	-O2 -Wall -Wextra
GPROF     = gprof
RM        = rm  -rf
LINK      = g++

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN)


$(BIN): $(LINKOBJ)
	$(LINK) $(LINKOBJ) -o $(BIN) $(LIBS)

$(LINKOBJ): $(SOURSE)
	$(CPP) -c $(SOURSE) -o $(OBJ) $(CXXFLAGS)
