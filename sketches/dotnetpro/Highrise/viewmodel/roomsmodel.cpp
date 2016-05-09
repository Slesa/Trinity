#include "viewmodel/roomsmodel.h"
#include <QDebug>

RoomsModel::RoomsModel(const QList<Room*>& rooms)
    : _rooms(rooms)
{
    foreach(Room* room, rooms) {
        connect(room, SIGNAL(nameChanged(Room*)), SLOT(onDataChanged(Room*)) );
        connect(room, SIGNAL(lightStateChanged(Room*)), SLOT(onDataChanged(Room*)) );
        connect(room, SIGNAL(roomStateChanged(Room*)), SLOT(onDataChanged(Room*)) );
    }
}

void RoomsModel::onDataChanged(Room* room) {
    qDebug() << "Name changed to " << room->name();

    auto row = _rooms.indexOf(room);
    auto index = this->index(row);
    emit dataChanged(index, index);
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
