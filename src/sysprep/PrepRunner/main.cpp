#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "systeminfo.h"
#include "runner.h"
#include "commandlineparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Preparation Runner");
    QCoreApplication::setApplicationVersion("0.1");
    QGuiApplication app(argc, argv);

    Settings settings;
    CommandLineParser::readArguments(app, settings);

    Runner runner(settings);
    SystemInfo systemInfo;
    auto validStart = runner.hasRootRights();
#ifdef QT_DEBUG
    validStart = true;
#endif
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("systeminfo", &systemInfo);
    engine.rootContext()->setContextProperty("runner", &runner);
    engine.rootContext()->setContextProperty("settings", &settings);
    QString entryPoint = validStart ? QStringLiteral("qrc:/main.qml") : QStringLiteral("qrc:/norootmsg.qml");
    engine.load(QUrl(entryPoint));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
