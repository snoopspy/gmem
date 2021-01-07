QT       += core
QT       -= gui
TARGET = qt_test
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
include(../../../gmem.pri)
SOURCES += main.cpp
DESTDIR = $${PWD}/../../../bin
