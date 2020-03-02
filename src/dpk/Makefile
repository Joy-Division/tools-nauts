#!/usr/bin/env make
#
# POLICENAUTS Toolbox
# Makefile for DPK Tools
#

TOP    = ../..
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib
MKDIR  = $(TOP)/make

include $(MKDIR)/mkdefs.mk

###############################################################################

C_WARNINGS = -Wall
C_SILENCES =
C_DEFINES  =
C_INCLUDES = -I$(INCDIR)
C_OPTIONS  = -g -O2

CXX_WARNINGS = $(C_WARNINGS)
CXX_SILENCES = $(C_SILENCES)
CXX_DEFINES  = $(C_DEFINES)
CXX_INCLUDES = $(C_INCLUDES)
CXX_OPTIONS  = $(C_OPTIONS)

###############################################################################

all: tools
tools: dpk_extract

$(LIBDIR)/libshared.a:
	$(MAKE) -C $(TOP)/src/shared install

dpk_extract: $(LIBDIR)/libshared.a
	$(CC) $(CFLAGS) $@.c -L$(LIBDIR) -lshared -o $@

install: tools
	cp -p ./dpk_extract     $(BINDIR)/dpk_extract
	cp -p ./dpk_extract.bat $(BINDIR)/dpk_extract.bat

###############################################################################

clean:\
	clean_obj \
	clean_lib \
	clean_exe

clean_obj:
	-rm *.o *.obj

clean_lib:
# PLACEHOLDER

clean_exe:
	-rm dpk_extract

clean_inst:
	-rm $(BINDIR)/dpk_extract
	-rm $(BINDIR)/dpk_extract.bat
