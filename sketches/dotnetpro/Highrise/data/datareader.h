#ifndef DATAREADER_H
#define DATAREADER_H
#include <QList>

class QDomElement;
class QString;
class Building;
class Floor;
class Room;

class DataReader
{
    static const QString fileName;
    static const QString tagRoot;
    static const QString tagId;
    static const QString tagName;
    static const QString tagBuilding;
    static const QString tagFloor;
    static const QString tagRoom;
    static const QString tagRoomState;
    static const QString tagLightState;

public:
    DataReader();
    QList<Building*> read();
    Building* parseBuildingElement(QDomElement& root);
    Floor* parseFloorElement(QDomElement& root);
    Room* parseRoomElement(QDomElement& root);
};

#endif // DATAREADER_H
