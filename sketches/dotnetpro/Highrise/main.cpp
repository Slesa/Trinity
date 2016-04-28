#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "data/datareader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataReader dataReader;
    if( !dataReader.read() )
        return -1;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

