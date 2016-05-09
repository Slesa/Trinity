#include "viewmodel/roomsmodel.h"

RoomsModel::RoomsModel(const QList<Room*>& rooms)
    : _rooms(rooms)
{
}


QVariant RoomsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
         return QVariant();

     auto room = _rooms.at(index.row());

     switch (role) {
     case IdRole:
         return room->id();
     case NameRole:
         return room->name();
     case LightStateRole:
         return room->lightState()==LightState::On ? 1 : 0;
     case RoomStateRole:
         return room->roomState()==RoomState::Ok ? 0 : 1;
     default:
         return QVariant();
     }
}

int RoomsModel::rowCount(const QModelIndex &parent) const
{
    return _rooms.count();
}

QHash<int, QByteArray> RoomsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[LightStateRole] = "lightstate";
    roles[RoomStateRole] = "roomstate";
    return roles;
}
