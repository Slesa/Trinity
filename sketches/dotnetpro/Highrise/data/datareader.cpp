#include "data/datareader.h"
#include "model/building.h"
#include <QFile>
#include <QDomDocument>
#include <QQmlApplicationEngine>
#include <QDebug>

const QString DataReader::fileName = QStringLiteral(":/highrise.xml");
const QString DataReader::tagRoot = "highrise";
const QString DataReader::tagId = "id";
const QString DataReader::tagName = "name";
const QString DataReader::tagBuilding = "building";
const QString DataReader::tagFloor = "floor";
const QString DataReader::tagRoom = "room";
const QString DataReader::tagRoomState = "roomstate";
const QString DataReader::tagLightState = "lightstate";

DataReader::DataReader()
{
}

QList<Building*> DataReader::read() {
    QList<Building*> buildings;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file " << fileName << ":\n" << file.errorString();
        return buildings;
    }

//    qDebug() << "XML, reading file " << fileName;

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument domDocument;
    if (!domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        qDebug() << "Parse error at line " << errorLine << ", column " << errorColumn << ":\n" << errorStr;
        return buildings;
    }

//    qDebug() << "XML, found root tag ";

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != tagRoot) {
        qDebug() << "The file is not an HighRise file.";
        return buildings;
    }
    if (root.hasAttribute("version") && root.attribute("version") != "1.0") {
        qDebug() << "The file is not an HighRise version 1.0 file.";
        return buildings;
    }

    QDomElement child = root.firstChildElement(tagBuilding);
    if(!child.isNull()) {
//        qDebug() << "XML, reading buildings";
        auto building = parseBuildingElement(child);
        if(building!=nullptr) {
            buildings.append(building);
        }
        child = child.nextSiblingElement(tagBuilding);
    }

//    qDebug() << "XML, " << buildings.count() << " building(s) found";
    return buildings;
}

Building* DataReader::parseBuildingElement(QDomElement& root) {
    int id = root.attribute(tagId).toInt();
    QString name = root.attribute(tagName);

    auto building = new Building(id, name);

    QDomElement child = root.firstChildElement(tagFloor);
    while (!child.isNull()) {
        auto floor = parseFloorElement(child);
        if( floor!=nullptr ) {
//            qDebug() << "XML, adding floor " << floor->id();
            building->floors().append(floor);
        }
        child = child.nextSiblingElement(tagFloor);
    }

//    qDebug() << "XML, " << building->floors().count() << " floor(s) found";
    return building;
}

Floor* DataReader::parseFloorElement(QDomElement& root) {
    int id = root.attribute(tagId).toInt();

    auto floor = new Floor(id);
    QDomElement child = root.firstChildElement(tagRoom);
    while (!child.isNull()) {
        auto room = parseRoomElement(child);
        if( room!=nullptr ) {
            QString lightstate = ", Light ";
            lightstate += (room->lightState()==LightState::Off) ? QString("off"):QString("on");
            QString roomstate = ", State ";
            roomstate += (room->roomState()==RoomState::Ok) ? QString("ok"):QString("error");
            /* qDebug() << "XML, adding room "
                     << room->id()
                     << " (" << room->name() << ")" << lightstate << roomstate; */
            floor->rooms().append(room);
        }
        child = child.nextSiblingElement(tagRoom);
    }

//    qDebug() << "XML, " << floor->rooms().count() << " room(s) found";
    return floor;
}

Room* DataReader::parseRoomElement(QDomElement& root) {
    int id = root.attribute(tagId).toInt();
    QString name = root.attribute(tagName);
    auto roomState = static_cast<RoomState>(root.attribute(tagRoomState).toInt());
    auto lightState = static_cast<LightState>(root.attribute(tagLightState).toInt());
    auto room = new Room(id, name);
    room->setLightState(lightState);
    room->setRoomState(roomState);
    return room;
}
