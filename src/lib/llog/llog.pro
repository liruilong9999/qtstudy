QT -= gui

TEMPLATE = lib
DEFINES += LLOG_LIBRARY
include($$PWD/../../../qtcode.pri)
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
    llog.cpp

HEADERS += \
    llog_global.h \
    llog.h

INCLUDEPATH += $$DEPENCE_DIR
CONFIG(debug,debug|release) : TARGET = llogd
CONFIG(release,debug|release) : TARGET = llog

target.path = $$BIN_DIST_DIR/lib

incfiles.files = $$HEADERS
incfiles.path = $$BIN_DIST_DIR/include/llog

INSTALLS += target incfiles
DESTDIR = $$BIN_DIST_DIR
