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
     case IdRole:
         return room->id();
     case NameRole:
         return room->name();
     case LightStateRole:
         return room->lightState()==LightState::On ? tr("On") : tr("Off");
     case RoomStateRole:
         return room->roomState()==RoomState::Ok ? tr("Ok") : tr("Error");
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
