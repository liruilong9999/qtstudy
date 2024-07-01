QT       += core gui
TEMPLATE = lib
include($$PWD/../../../qtcode.pri)

CONFIG += c++11
CONFIG += plugin

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    pluginb.cpp

HEADERS += \
    pluginb.h

OTHER_FILES += plugin_info.json

INCLUDEPATH += $$BIN_DIST_DIR/include

target.path = $$BIN_DIST_DIR/plugins
INSTALLS += target


