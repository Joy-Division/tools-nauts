#
# POLICENAUTS Toolbox
# Makefile for Shared Code
#

TOP    = ../..
BINDIR = $(TOP)/bin
INCDIR = $(TOP)/include
LIBDIR = $(TOP)/lib
MKDIR  = $(TOP)/make

include $(MKDIR)/mkdefs.mk

#---------------------------------------------------------------------------#

CFLAGS = -Wall -I$(INCDIR) -g -O2

TARGET  = libshared.a
OBJECTS = mkpath.o

%.o: %.c
	$(CC) $(CFLAGS) $^ -c
#	objdump -dl $@ > $@.txt

#---------------------------------------------------------------------------#

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -cr $@ $(OBJECTS)

install: $(TARGET)
	cp -p $(TARGET) $(LIBDIR)/$(TARGET)

#---------------------------------------------------------------------------#

clean:\
	clean_obj \
	clean_lib \
	clean_exe

clean_obj:
	-rm *.o *.obj

clean_lib:
	-rm *.a *.lib

clean_inst:
	-rm $(LIBDIR)/$(TARGET)
