#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QDebug>

class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)
    Q_PROPERTY(QString attribute READ attribute NOTIFY attributeChanged)
public:
    explicit MainController(QObject *parent = 0);

    QString property() const {
        qDebug() << "Getting property " << _property;
        return _property;
    }
    void setProperty(const QString& value) {
        qDebug() << "Setting property to " << value;
        if( _property==value ) return;
        _property = value;
        emit propertyChanged();
    }

    QString attribute() const { return _attribute; }
signals:
    void propertyChanged();
    void attributeChanged();

public slots:
    void changeAttribute(const QString& value) {
        if( _attribute==value ) return;
        qDebug() << "Setting attribute to " << value;
        _attribute = value;
        emit attributeChanged();
    }

private:
    QString _property;
    QString _attribute;
};

#endif // MAINCONTROLLER_H
