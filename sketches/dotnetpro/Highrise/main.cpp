#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "data/datareader.h"
#include "viewmodel/buildingmodel.h"
#include "viewmodel/roomsmodel.h"
#include "model/building.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataReader dataReader;
    auto buildings = dataReader.read();
    auto building = buildings[0];
    auto buildingModel = new BuildingModel(building);
    auto buildingProxy = new BuildingProxy();
    auto rooms = building->getRooms();
    auto roomsModel = new RoomsModel(*rooms);
    buildingProxy->setSourceModel(buildingModel);

//    auto roomsModel = new RoomsModel(building->floors());

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    context->setContextProperty("buildingModel", buildingModel);
    context->setContextProperty("buildingProxy", buildingProxy);
    context->setContextProperty("roomsModel", roomsModel);


    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

