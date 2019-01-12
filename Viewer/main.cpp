#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "viewer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    Viewer viewer;
    viewer.initModels(engine);
    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

