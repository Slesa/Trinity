#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H
#include <QAbstractListModel>
#include "model/room.h"

class RoomsModel : public QAbstractListModel
{
    enum RoomRoles {
        IdRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        LightStateRole = Qt::UserRole + 3,
        RoomStateRole = Qt::UserRole + 4,
    };
public:
    RoomsModel(const QList<Room*>& rooms);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Room*> _rooms;
};

#endif // ROOMSMODEL_H
