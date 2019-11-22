#
# POLICENAUTS Toolbox
# Top-Level Makefile
#

TOP    = .
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib

MISC  = $(TOP)/misc
DATA  = $(TOP)/data
SOUND = $(TOP)/sound

#---------------------------------------------------------------------------#

all: shared tools

shared:
	$(MAKE) -C $(MISC) install

tools:
	$(MAKE) -C $(DATA)/dpk
#	$(MAKE) -C $(DATA)/pac
#	$(MAKE) -C $(SOUND)/pac

install:
	$(MAKE) -C $(DATA)/dpk install
#	$(MAKE) -C $(DATA)/pac install
#	$(MAKE) -C $(SOUND)/pac install

#---------------------------------------------------------------------------#

clean:\
	clean_all \
	clean_lib

clean_all:
	$(MAKE) -C $(MISC) clean
	$(MAKE) -C $(DATA)/dpk clean
#	$(MAKE) -C $(DATA)/pac clean
#	$(MAKE) -C $(SOUND)/pac clean

clean_lib:
	-rm $(LIBDIR)/*.a
	-rm $(LIBDIR)/*.lib
