QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../../../qtcode.pri)
INCLUDEPATH += $$BIN_DIST_DIR/include
INCLUDEPATH += $$SRC_DIR/common
INCLUDEPATH += $$DEPENCE_DIR

CONFIG(release, debug|release){
    LIBS += -L$$BIN_DIST_DIR/lib/ -lpluginmanager
    }else
    {
        LIBS += -L$$BIN_DIST_DIR/lib/ -lpluginmanagerd
    }

config.files = $$PROJECT_DIR/app/config
config.path = $$BIN_DIST_DIR

INSTALLS += config

SOURCES += \
    main.cpp 

DESTDIR = $$BIN_DIST_DIR
