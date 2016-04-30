#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H
#include <QAbstractListModel>
#include "model/room.h"

class Building;

class BuildingModel : public QAbstractListModel
{
    enum RoomRoles {
        IdRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        LightStateRole = Qt::UserRole + 3,
        RoomStateRole = Qt::UserRole + 4,
    };

public:
    BuildingModel(Building* building);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Room*> _rooms;
};

#endif // BUILDINGMODEL_H
