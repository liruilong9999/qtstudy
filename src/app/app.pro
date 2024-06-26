QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

include($$PWD/../../qtcode.pri)

INCLUDEPATH += $$DEPENCE_DIR/vlc/include
INCLUDEPATH += $$DEPENCE_DIR/vlc/include/vlc

DEPENDPATH += $$DEPENCE_DIR/vlc/include
DEPENDPATH += $$DEPENCE_DIR/vlc/include/vlc

LIBS += -L$$DEPENCE_DIR/vlc/lib/ -lvlc
LIBS += -L$$DEPENCE_DIR/vlc/lib/ -lvlccore
LIBS += -L$$DEPENCE_DIR/vlc/lib/ -llibvlc
LIBS += -L$$DEPENCE_DIR/vlc/ -llibvlccore

message($$INCLUDEPATH)

DESTDIR = $$BIN_DIST_DIR
