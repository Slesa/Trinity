#include "viewmodel/buildingmodel.h"
#include "model/building.h"
#include <QDebug>

BuildingModel::BuildingModel(Building* building)
{
    foreach(auto floor, building->floors()) {
        _rooms.append(floor->rooms());
    }
}

QVariant BuildingModel::data(const QModelIndex &index, int role) const
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
         return room->roomState()==RoomState::Ok ? 1 : 0;
     default:
         return QVariant();
     }
}

bool BuildingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "Setting data";
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount()) {
        qDebug() << "Index not found";
        return false;
    }

    auto room = _rooms.at(index.row());
    switch (role) {
    case NameRole:
        room->setName(value.toString());
        break;
    case LightStateRole:
        qDebug() << "Setting light state " << value;
        room->setLightState(value==1 ? LightState::On : LightState::Off);
        break;
    case RoomStateRole:
        qDebug() << "Setting room state" << value;
        room->setRoomState(value==0 ? RoomState::Ok : RoomState::Error);
        break;
    default:
        return false;
    }
    emit dataChanged(index, index);
    return true;
}

int BuildingModel::rowCount(const QModelIndex &parent) const
{
    return _rooms.count();
}

QHash<int, QByteArray> BuildingModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[LightStateRole] = "lightstate";
    roles[RoomStateRole] = "roomstate";
    return roles;
}

bool BuildingProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index1 = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(index1, BuildingModel::NameRole).toString().contains(filterRegExp());
}
