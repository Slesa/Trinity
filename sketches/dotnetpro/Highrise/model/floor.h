#ifndef FLOOR_H
#define FLOOR_H

#include "model/room.h"
#include <QObject>

class Floor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QList<Room*> rooms READ rooms)
public:
    explicit Floor(int id, QObject *parent = 0);

    int id() const {
        return _id;
    }

    QList<Room*>& rooms() {
        return _rooms;
    }

signals:

private:
    int _id;
    QList<Room*> _rooms;
};

#endif // FLOOR_H
