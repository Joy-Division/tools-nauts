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

SRCDIR = $(TOP)/src

#---------------------------------------------------------------------------#

all: shared tools install

shared:
	$(MAKE) -C $(SRCDIR)/shared install

tools:
	$(MAKE) -C $(SRCDIR)/dpk $@
#	$(MAKE) -C $(SRCDIR)/pac $@
#	$(MAKE) -C $(SRCDIR)/sound $@

install:
	$(MAKE) -C $(SRCDIR)/dpk $@
#	$(MAKE) -C $(SRCDIR)/pac $@
#	$(MAKE) -C $(SRCDIR)/sound $@

#---------------------------------------------------------------------------#

clean_all:\
	clean \
	clean_lib

clean:
	$(MAKE) -C $(SRCDIR)/shared $@
	$(MAKE) -C $(SRCDIR)/dpk $@
#	$(MAKE) -C $(SRCDIR)/pac $@
#	$(MAKE) -C $(SRCDIR)/sound $@

clean_lib:
	-rm $(LIBDIR)/*.a
	-rm $(LIBDIR)/*.lib
