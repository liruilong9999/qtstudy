QT       += core gui widgets
TEMPLATE = lib
DEFINES += APPSKELETON_LIBRARY

CONFIG += c++11

include($$PWD/../../../qtcode.pri)
SOURCES += \
    appskeleton.cpp \
    ipluginview.cpp

HEADERS += \
    appskeleton.h \
    appskeleton_gloabal.h \
    ipluginview.h
FORMS += \
    appskeleton.ui

INCLUDEPATH += $$DEPENCE_DIR

CONFIG(release, debug|release){
    LIBS += -L$$BIN_DIST_DIR/lib/ -lllog
    }else
    {
        LIBS += -L$$BIN_DIST_DIR/lib/ -lllogd
    }


CONFIG(debug,debug|release) : TARGET = appskeletond
CONFIG(release,debug|release) : TARGET = appskeleton

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/appskeleton

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR


