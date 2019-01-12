TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    viewer2.cpp \
    jumplistmodel.cpp \
    inventarylistmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    viewer2.h \
    jumplistmodel.h \
    inventarylistmodel.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DialogPoint/release/ -lDialogPoint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DialogPoint/debug/ -lDialogPoint
else:unix: LIBS += -L$$OUT_PWD/../DialogPoint/ -lDialogPoint

INCLUDEPATH += $$PWD/../DialogPoint
DEPENDPATH += $$PWD/../DialogPoint
