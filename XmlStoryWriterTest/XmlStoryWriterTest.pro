#-------------------------------------------------
#
# Project created by QtCreator 2019-01-10T08:53:18
#
#-------------------------------------------------

QT       += xml testlib

QT       -= gui

TARGET = tst_xmlstorywritertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_xmlstorywritertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DialogPoint/release/ -lDialogPoint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DialogPoint/debug/ -lDialogPoint
else:unix: LIBS += -L$$OUT_PWD/../DialogPoint/ -lDialogPoint

INCLUDEPATH += $$PWD/../DialogPoint
DEPENDPATH += $$PWD/../DialogPoint



