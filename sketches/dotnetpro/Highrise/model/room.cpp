#include "model/room.h"

Room::Room(int id, const QString& name, QObject *parent)
    : QObject(parent)
    , _id(id)
    , _name(name)
    , _roomState(RoomState::Ok)
    , _lightState(LightState::Off)
{
}

