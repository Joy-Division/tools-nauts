#!/usr/bin/env make
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
# RULES & DEFINES
#---------------------------------------------------------------------------#

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

TARGET  = libshared.a
OBJECTS = mkpath.o

%.o: %.c
	$(CC) $(CFLAGS) -c $^
#	objdump -dl $@ > $@.txt

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^
#	objdump -dl $@ > $@.txt

#---------------------------------------------------------------------------#
# BUILD & INSTALL
#---------------------------------------------------------------------------#

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -cr $@ $(OBJECTS)

install: $(TARGET)
	cp -p $(TARGET) $(LIBDIR)/$(TARGET)

#---------------------------------------------------------------------------#
# CLEANUP
#---------------------------------------------------------------------------#

clean:\
	clean_obj \
	clean_lib

clean_obj:
	-rm *.o *.obj

clean_lib:
	-rm *.a *.lib

clean_inst:
	-rm $(LIBDIR)/$(TARGET)
