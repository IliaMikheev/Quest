#-------------------------------------------------
#
# Project created by QtCreator 2019-01-10T08:42:13
#
#-------------------------------------------------

QT       -= gui

TARGET = DialogPoint
TEMPLATE = lib

DEFINES += DIALOGPOINT_LIBRARY

SOURCES += dialogpoint.cpp \
    xmlstoryreader.cpp \
    xmlstorywriter.cpp

HEADERS += dialogpoint.h\
        dialogpoint_global.h \
    xmlstoryreader.h \
    xmlstorywriter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
