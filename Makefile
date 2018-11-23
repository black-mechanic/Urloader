#############################################################################
# Makefile for building: Urloader class and test
# Template: app
# Command: make
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -std=gnu++11 -Wall -W -fPIC $(DEFINES)
INCPATH       = -I/src -I. -I/usr/lib/x86_64-linux-gnu 
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = Urloader_1.0.0
DISTDIR = /home/nuh/IDEProj/Urloader
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS) /usr/lib/x86_64-linux-gnu/libcurl.so 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cpp src/urloader.cpp 
OBJECTS       = main.o urloader.o
DIST		      = src/urloader.hpp src/main.cpp src/urloader.cpp
DESTDIR       = 
TARGET        = Urloader_test



$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

Makefile:
all: Makefile $(TARGET)

####### Compile

main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

urloader.o: src/urloader.cpp src/urloader.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o urloader.o src/urloader.cpp

####### Clean
clean: -$(DEL_FILE) $(OBJECTS)
