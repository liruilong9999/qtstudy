QT       += core
TEMPLATE = lib
DEFINES += PLUGINSMANAGER_LIBRARY

CONFIG += c++11

include($$PWD/../../../qtcode.pri)
SOURCES += \
    pluginmanager.cpp 

HEADERS += \
    plugininterface.h\
    pluginmanager.h\
    pluginmanager_gloabal.h

CONFIG(debug,debug|release) : TARGET = pluginmanagerd
CONFIG(release,debug|release) : TARGET = pluginmanager

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/pluginmanager

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR


