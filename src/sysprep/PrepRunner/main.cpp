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
    auto validStart = runner.hasRootRights();
#ifdef QT_DEBUG
    validStart = true;
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("systeminfo", &systemInfo);
    engine.rootContext()->setContextProperty("runner", &runner);
    QString entryPoint = validStart ? QStringLiteral("qrc:/main.qml") : QStringLiteral("qrc:/norootmsg.qml");
    engine.load(QUrl(entryPoint));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
