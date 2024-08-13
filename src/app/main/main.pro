QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../../../qtcode.pri)

#INCLUDEPATH += $$BIN_DIST_DIR/include
INCLUDEPATH += $$DEPENCE_DIR

#message($$INCLUDEPATH)

CONFIG(release, debug|release){
    LIBS += -L$$BIN_DIST_DIR/lib/ -lpluginmanager
    LIBS += -L$$BIN_DIST_DIR/lib/ -lappskeleton
    }else
    {
        LIBS += -L$$BIN_DIST_DIR/lib/ -lpluginmanagerd
    LIBS += -L$$BIN_DIST_DIR/lib/ -lappskeletond
    }

config.files = $$PROJECT_DIR/app/config
config.path = $$BIN_DIST_DIR

INSTALLS += config

SOURCES += \
    main.cpp \
    #mainwindow.cpp

HEADERS += \
    #mainwindow.h

FORMS   += \
    #mainwindow.ui

DESTDIR = $$BIN_DIST_DIR
