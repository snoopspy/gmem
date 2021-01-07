CONFIG -= qt
include(../../../gmem.pri)
DEFINES += GMEM_GLOBAL_HOOK
SOURCES += *.cpp
DESTDIR = $${PWD}/../../../bin
