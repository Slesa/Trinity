#ifndef SYSTEMMODEL_H
#define SYSTEMMODEL_H

#include <QAbstractListModel>

class SystemModel : public QAbstractListModel
{
    static const char* strName;
    static const char* strInstaller;
public:
    enum SystemRole {
        NameRole = Qt::DisplayPropertyRole,
        InstallerRole = Qt::UserRole
    };
    Q_ENUM(SystemRole)

    SystemModel(QObject* parent=nullptr);

    int rowCount(const QModelIndex& = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE void append(const QString& name, const QString& installer);
    Q_INVOKABLE void set(int row, const QString& name, const QString& installer);
    Q_INVOKABLE void remove(int row);

private:
    struct System {
        QString name;
        QString installer;
    };

    QList<System> m_systems;
};

#endif // SYSTEMMODEL_H
