TEMPLATE = app
CONFIG += debug
SOURCES = ../src/main.cpp
LIBS += -L ../lib -lGraflib
TARGET = ../bin/test
OBJECTS_DIR = ../tmp
INCLUDEPATH += ../inc ../src
