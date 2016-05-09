#include "model/building.h"

Building::Building(int id, const QString& name, QObject *parent)
    : QObject(parent)
    , _id(id)
    , _name(name)
{
}

QList<Room*>* Building::getRooms() {
    auto rooms = new QList<Room*>();
    foreach (auto floor, floors() ) {
        rooms->append(floor->rooms());
    }
    return rooms;
}
