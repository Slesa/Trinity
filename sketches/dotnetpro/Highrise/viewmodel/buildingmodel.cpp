#include "viewmodel/buildingmodel.h"
#include "model/building.h"

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
     case RoomRoles::NameRole:
         return room->name();
     case LightStateRole:
         return room->lightState();
     case RoomStateRole:
         return room->roomState();
     default:
         return QVariant();
     }
}

int BuildingModel::rowCount(const QModelIndex &parent) const
{
    return _rooms.count();
}

QHash<int, QByteArray> BuildingModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[LightStateRole] = "lightsttae";
    roles[RoomStateRole] = "roomstate";
    return roles;
}
