#include "maincontroller.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();

    QString currPath = QDir::currentPath();
    context->setContextProperty("currentPath", currPath);

    QScreen *screen = QApplication::screens().at(0);
    int width = screen->availableSize().width();
    context->setContextProperty("availableWidth", width);
    int height = screen->availableSize().height();
    context->setContextProperty("availableHeight", height);

    MainController* mainController = new MainController();
    context->setContextProperty("mainController", mainController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}

