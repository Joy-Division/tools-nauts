#
# POLICENAUTS Toolbox
# Common Definitions
#

#---------------------------------------------------------------------------#
# C/C++ Compiler ID
#---------------------------------------------------------------------------#
# Override defines for the default values of CC & CXX.
# Command-line Example: CC=$(GCC_WIN32) CXX=$(GXX_WIN32)

# MinGW GCC toolchain
GCC_WIN32 = i686-w64-mingw32-gcc
GXX_WIN32 = i686-w64-mingw32-g++
GCC_WIN64 = x86_64-w64-mingw32-gcc
GXX_WIN64 = x86_64-w64-mingw32-g++

# MSYS2 GCC toolchain
GCC_MSYS32 = i686-pc-msys-gcc
GXX_MSYS32 = i686-pc-msys-g++
GCC_MSYS64 = x86_64-pc-msys-gcc
GXX_MSYS64 = x86_64-pc-msys-g++

#---------------------------------------------------------------------------#
# C/C++ Compiler Flags
#---------------------------------------------------------------------------#
# Default definitions of CFLAGS & CXXFLAGS.
# These variables shall be defined in the including Makefile.

CFLAGS =\
	$(C_WARNINGS) \
	$(C_SILENCES) \
	$(C_DEFINES)  \
	$(C_INCLUDES) \
	$(C_OPTIONS)

CXXFLAGS =\
	$(CXX_WARNINGS) \
	$(CXX_SILENCES) \
	$(CXX_DEFINES)  \
	$(CXX_INCLUDES) \
	$(CXX_OPTIONS)
