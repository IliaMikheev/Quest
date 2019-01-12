#include <QApplication>
#include <QQmlApplicationEngine>
#include "viewer2.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Viewer2 viewer;
    viewer.initModels(engine);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
