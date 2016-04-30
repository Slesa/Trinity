#ifndef ROOM_H
#define ROOM_H
#include <QObject>

enum RoomState {
    Ok,
    Error
};

enum LightState {
    Off,
    On
};

class Room : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(RoomState roomState READ roomState WRITE setRoomState NOTIFY roomStateChanged)
    Q_PROPERTY(LightState lightState READ lightState WRITE setLightState NOTIFY lightStateChanged)

public:
    explicit Room(int id, const QString& name, QObject *parent = 0);

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

    RoomState roomState() const {
        return _roomState;
    }
    void setRoomState(const RoomState value) {
        if( _roomState==value ) return;
        _roomState = value;
        emit roomStateChanged();
    }

    LightState lightState() const {
        return _lightState;
    }
    void setLightState(const LightState value) {
        if( _lightState==value ) return;
        _lightState = value;
        emit lightStateChanged();
    }

signals:
    void nameChanged();
    void roomStateChanged();
    void lightStateChanged();

public slots:

private:
    int _id;
    QString _name;
    RoomState _roomState;
    LightState _lightState;
};

#endif // ROOM_H
