# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Urloader

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS = \
   $$PWD/src/urloader.hpp

SOURCES = \
   $$PWD/src/main.cpp \
   $$PWD/src/urloader.cpp

INCLUDEPATH += /usr/lib/x86_64-linux-gnu/

LIBS = /usr/lib/x86_64-linux-gnu/libcurl.so

#DEFINES = 






