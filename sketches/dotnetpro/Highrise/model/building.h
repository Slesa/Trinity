#ifndef BUILDING_H
#define BUILDING_H

#include "model/floor.h"
#include <QObject>

class Building : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<Floor*> floors READ floors)
public:
    explicit Building(int id, const QString& name, QObject *parent = 0);

    int id() const {
        return _id;
    }

    QString name() const {
        return _name;
    }
    void setName(const QString& value) {
        if( _name==value ) return;
        _name = value;
        emit nameChanged();
    }

    QList<Floor*>& floors() {
        return _floors;
    }

signals:
    void nameChanged();

public slots:
private:
    int _id;
    QString _name;
    QList<Floor*> _floors;
};

#endif // BUILDING_H
