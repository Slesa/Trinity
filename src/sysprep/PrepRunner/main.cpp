#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "systeminfo.h"
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    SystemInfo systemInfo;
    Runner runner;
    if( runner.ensureRoot() )
        return 0;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("systeminfo", &systemInfo);
    engine.rootContext()->setContextProperty("runner", &runner);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
