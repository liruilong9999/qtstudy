QT -= gui

TEMPLATE = lib
DEFINES += COMMUNATEMODULE_LIBRARY
include($$PWD/../../../qtcode.pri)
INCLUDEPATH += ../
INCLUDEPATH += $$DEPENCE_DIR

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communatemodule.cpp

HEADERS += \
    communatemodule_global.h \
    communatemodule.h

CONFIG(release, debug|release){
    LIBS += -L$$BIN_DIST_DIR/lib/ -lllog
    }else
    {
        LIBS += -L$$BIN_DIST_DIR/lib/ -lllogd
    }

CONFIG(debug,debug|release) : TARGET = communatemoduled
CONFIG(release,debug|release) : TARGET = communatemodule

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/communatemodule

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR
