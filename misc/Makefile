#
# POLICENAUTS Toolbox
# Makefile for Shared Components
#

TOP    = ..
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

TARGET  = libmisc.a
OBJECTS = mkpath.o

%.o: %.c
	$(CC) $(CFLAGS) $^ -c
#	objdump -dl $@ > $@.txt

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

clean_exe:
# PLACEHOLDER
