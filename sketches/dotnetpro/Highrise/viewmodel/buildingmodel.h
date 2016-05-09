#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
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
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    QList<Room*> GetRooms() {
        return _rooms;
    }

private:
    QList<Room*> _rooms;
    friend class BuildingProxy;
};

class BuildingProxy: public QSortFilterProxyModel
{
protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // BUILDINGMODEL_H
