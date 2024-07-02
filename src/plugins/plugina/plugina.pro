QT       += core gui

include($$PWD/../../../qtcode.pri)

TEMPLATE = lib
DEFINES +=PLUGINA_LIBRARY

CONFIG += c++11
CONFIG += plugin

SOURCES += \
    plugina.cpp 

HEADERS += \
    plugina.h \
    plugina_global.h

DEFINES += QT_DEPRECATED_WARNINGS
OTHER_FILES += plugin_info.json

INCLUDEPATH += $$BIN_DIST_DIR/include

#DESTDIR = $$BIN_DIST_DIR/plugins

target.path = $$PLUGIN_PATH
INSTALLS += target

