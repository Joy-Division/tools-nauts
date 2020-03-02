#!/usr/bin/env make
#
# POLICENAUTS Toolbox
# Top-Level Makefile
#

TOP    = .
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib
MKDIR  = $(TOP)/make

#include $(MKDIR)/mkdefs.mk

###############################################################################

SRCDIR = $(TOP)/src
MAKEFILE ?= Makefile

###############################################################################

all: shared tools install

shared:
	$(MAKE) -C $(SRCDIR)/shared install

tools install:
	$(MAKE) -C $(SRCDIR)/dpk   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound -f$(MAKEFILE) $@

###############################################################################

clean_all: clean clean_inst

clean clean_inst:
	$(MAKE) -C $(SRCDIR)/shared -f$(MAKEFILE) $@
	$(MAKE) -C $(SRCDIR)/dpk    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound  -f$(MAKEFILE) $@
