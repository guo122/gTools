#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T19:01:55
#
#-------------------------------------------------

QT       -= gui

TARGET = ODWayV
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ODWayV.cpp \
    ODVTime.cpp \
    TreeModel.cpp \
    TreeItem.cpp \
    ODVGoblin.cpp \
    ODVCKK.cpp \
    ODNotification.mm \
    ODVEfg.cpp

HEADERS += \
        ODWayV.h \
    ODVTime.h \
    TreeModel.h \
    TreeItem.h \
    ODVGoblin.h \
    ODVCKK.h \
    ODNotification.h \
    ODVEfg.h

OBJECTIVE_SOURCES += ODNotification.mm

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../3rd/ODBase
DEPENDPATH += $$PWD/../3rd/ODBase
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
