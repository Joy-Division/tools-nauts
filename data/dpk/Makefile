#
# POLICENAUTS Toolbox
# Makefile for DPK Tools
#

TOP    = ../..
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib

# Windows (MinGW)
GCC_WIN32 = i686-w64-mingw32-gcc
GXX_WIN32 = i686-w64-mingw32-g++
GCC_WIN64 = x86_64-w64-mingw32-gcc
GXX_WIN64 = x86_64-w64-mingw32-g++

#---------------------------------------------------------------------------#

CFLAGS = -Wall -I$(INCDIR) -g -O2

all: tools
tools: dpk_extract

dpk_extract: dpk_extract.c
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@
	cp -p ./$@.bat $(BINDIR)/$@.bat

#---------------------------------------------------------------------------#

clean:\
	clean_obj \
	clean_exe

clean_obj:
	-rm *.o *.obj

clean_exe:
	-rm $(BINDIR)/dpk_extract
	-rm $(BINDIR)/dpk_extract.exe
	-rm $(BINDIR)/dpk_extract.bat
