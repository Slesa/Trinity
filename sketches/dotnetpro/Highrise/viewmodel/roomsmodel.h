#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H
#include <QAbstractItemModel>
#include "model/room.h"

class RoomsModel : public QAbstractItemModel
{
public:
    RoomsModel(const QList<Room*>& rooms);

private:
    QList<Room*> _rooms;
};

#endif // ROOMSMODEL_H
