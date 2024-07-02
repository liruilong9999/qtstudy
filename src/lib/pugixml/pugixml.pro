QT       += core
TEMPLATE = lib
DEFINES += PLUGINSMANAGER_LIBRARY

CONFIG += c++11

include($$PWD/../../../qtcode.pri)
SOURCES += \
    pugixml.cpp \
    pugiconfig.hpp

HEADERS += \
    pugixml.hpp

CONFIG(debug,debug|release) : TARGET = pugixmld
CONFIG(release,debug|release) : TARGET = pugixml

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/pugixml

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR


