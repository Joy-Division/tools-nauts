#
# POLICENAUTS Toolbox
# Top-Level Makefile
#

TOP    = .
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib

DATA  = $(TOP)/data
SOUND = $(TOP)/sound

#---------------------------------------------------------------------------#

all: data
data: data_dpk

data_dpk:
	$(MAKE) -C $(DATA)/dpk all

#data_pac:
#	$(MAKE) -C $(DATA)/pac all

#sound_pac:
#	$(MAKE) -C $(SOUND)/pac all

#---------------------------------------------------------------------------#

clean:\
	clean_obj \
	clean_lib \
	clean_exe

clean_obj:
	$(MAKE) -C $(DATA)/dpk clean_obj
#	$(MAKE) -C $(DATA)/pac clean_obj
#	$(MAKE) -C $(SOUND)/pac clean_obj

clean_lib:
	-rm $(LIBDIR)/*.a
	-rm $(LIBDIR)/*.lib

clean_exe:
	$(MAKE) -C $(DATA)/dpk clean_exe
#	$(MAKE) -C $(DATA)/pac clean_exe
#	$(MAKE) -C $(SOUND)/pac clean_exe
