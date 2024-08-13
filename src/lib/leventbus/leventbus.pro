QT += core

TEMPLATE = lib
DEFINES += LEVENTBUS_LIBRARY
include($$PWD/../../../qtcode.pri)
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    leventbus.cpp

HEADERS += \
    leventbus_global.h \
    leventbus.h

INCLUDEPATH += $$DEPENCE_DIR
CONFIG(debug,debug|release) : TARGET = leventbusd
CONFIG(release,debug|release) : TARGET = leventbus

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/leventbus

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR
