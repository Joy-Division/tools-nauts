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

#---------------------------------------------------------------------------#
# RULES & DEFINES
#---------------------------------------------------------------------------#

SRCDIR = $(TOP)/src
MAKEFILE ?= Makefile

#---------------------------------------------------------------------------#
# BUILD & INSTALL
#---------------------------------------------------------------------------#

all: shared tools install

shared:
	$(MAKE) -C $(SRCDIR)/shared install

tools:
	$(MAKE) -C $(SRCDIR)/dpk   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound -f$(MAKEFILE) $@

install:
	$(MAKE) -C $(SRCDIR)/dpk   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac   -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound -f$(MAKEFILE) $@

#---------------------------------------------------------------------------#
# CLEANUP
#---------------------------------------------------------------------------#

clean_all: clean clean_inst

clean:
	$(MAKE) -C $(SRCDIR)/shared -f$(MAKEFILE) $@
	$(MAKE) -C $(SRCDIR)/dpk    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound  -f$(MAKEFILE) $@

clean_inst:
	$(MAKE) -C $(SRCDIR)/shared -f$(MAKEFILE) $@
	$(MAKE) -C $(SRCDIR)/dpk    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/pac    -f$(MAKEFILE) $@
#	$(MAKE) -C $(SRCDIR)/sound  -f$(MAKEFILE) $@
