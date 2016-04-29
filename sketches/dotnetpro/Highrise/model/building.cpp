#include "model/building.h"

Building::Building(int id, const QString& name, QObject *parent)
    : QObject(parent)
    , _id(id)
    , _name(name)
{
}

