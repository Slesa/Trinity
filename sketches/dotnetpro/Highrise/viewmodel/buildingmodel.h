#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include "model/room.h"
#include <QDebug>

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
    friend class BuildingProxy;
};

class BuildingProxy: public QSortFilterProxyModel
{
//    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
public:
/*    QString filter() const {
        return _filter;
    }
    void setFilter(const QString& value) {
        qDebug() << "Setting filter";
        if( _filter==value ) return;
        _filter = value;
        emit filterChanged();
        this->invalidateFilter();
    }*/

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

//signals:
//    void filterChanged();

//private:
//    QString _filter;
};

#endif // BUILDINGMODEL_H
