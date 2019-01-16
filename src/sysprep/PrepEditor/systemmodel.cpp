#include "systemmodel.h"

const char* SystemModel::strName = "name";
const char* SystemModel::strInstaller = "installer";

SystemModel::SystemModel(QObject* parent)
    : QAbstractListModel(parent)
{
    m_systems.append({"Ubuntu", "apt-get install -y"});
    m_systems.append({"SuSE", "zypper install -y"});
    m_systems.append({"Arch", "yum install -y"});
    m_systems.append({"Ubuntu/Win", "apt-get install -y"});
    m_systems.append({"SuSE/Win", "zypper install -y"});
    m_systems.append({"Windows", "choco install -y"});
}

int SystemModel::rowCount(const QModelIndex&) const
{
    return m_systems.count();
}

QVariant SystemModel::data(const QModelIndex& index, int role) const
{
    if(index.row() < rowCount())
        switch(role) {
            case NameRole: return m_systems.at(index.row()).name;
            case InstallerRole: return m_systems.at(index.row()).installer;
        }
    return QVariant();
}

QHash<int, QByteArray> SystemModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { NameRole, strName },
        { InstallerRole, strInstaller }
    };
    return roles;
}

QVariantMap SystemModel::get(int row) const
{
    const System system = m_systems.value(row);
    return { {strName, system.name}, {strInstaller, system.installer} };
}

void SystemModel::append(const QString& name, const QString& installer)
{
    int row = 0;
    while(row<m_systems.count() && name > m_systems.at(row).name)
        row++;
    beginInsertRows(QModelIndex(), row, row);
    m_systems.insert(row, { name, installer});
    endInsertRows();
}

void SystemModel::set(int row, const QString& name, const QString& installer)
{
    if(row<0 || row>=rowCount())
        return;
    m_systems.replace(row, { name, installer });
    dataChanged(index(row, 0), index(row, 0), { NameRole, InstallerRole });
}

void SystemModel::remove(int row)
{
    if(row<0 || row>=rowCount())
        return;
    beginRemoveRows(QModelIndex(), row, row);
    m_systems.removeAt(row);
    endRemoveRows();
}
