#include "hotkeytable.h"
#include "sqlexception.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

const char* HotkeyTable::tableName = "hotkeys";
const char* HotkeyTable::fieldId = "id";
const char* HotkeyTable::fieldPackage = "package";
const char* HotkeyTable::fieldDescr = "descr";
const char* HotkeyTable::fieldSystems = "systems";


HotkeyTable::HotkeyTable()
{
}

QSqlQuery HotkeyTable::prepareInsertion()
{
    QSqlQuery q;
    if (!q.prepare(QString("insert into %1(%2, %3, %4) values(?, ?, ?)")
                   .arg(tableName)
                   .arg(fieldPackage)
                   .arg(fieldDescr)
                   .arg(fieldSystems)))
        throw new SqlException(q.lastError());
    return q;
}

QVariant HotkeyTable::addHotkey(QSqlQuery& q, int package, const QString& descr, int systems)
{
    q.addBindValue(package);
    q.addBindValue(descr);
    q.addBindValue(systems);
    q.exec();
    return q.lastInsertId();
}

Hotkey HotkeyTable::getById(int id)
{
    Hotkey hotkey;

    QSqlQuery query = findById(id);
    if(!query.next())
        return hotkey;

    hotkey.setId(id);

    int packageIdx = query.record().indexOf(fieldPackage);
    int package = query.value(packageIdx).toInt();
    hotkey.setPackage(package);

    int descrIdx = query.record().indexOf(fieldDescr);
    QString descr = query.value(descrIdx).toString();
    hotkey.setDescription(descr);

    int systemsIdx = query.record().indexOf(fieldSystems);
    int systems = query.value(systemsIdx).toInt();
    hotkey.setSystems((SystemFlags)systems);

    return hotkey;
}

QSqlQuery HotkeyTable::findById(int id)
{
    QSqlQuery query(QString("SELECT * FROM %1 WHERE %2=%3")
                    .arg(tableName)
                    .arg(fieldId)
                    .arg(id));
    return query;
}



class HotkeyInitializer : public TableInitializer
{
public:
    HotkeyInitializer();
    virtual QString getTableName();
    virtual QSqlError createTable();
};

static HotkeyInitializer s_hotkeyInitializer;

HotkeyInitializer::HotkeyInitializer()
{
    TableInitializers::getInstance().doRegister(this);
}

QString HotkeyInitializer::getTableName()
{
    return HotkeyTable::tableName;
}

QSqlError HotkeyInitializer::createTable()
{
    QSqlQuery q;
    if (!q.exec(QString("create table %1(%2 integer primary key, %3 integer, %4 varchar, %5 varchar)")
                .arg(HotkeyTable::tableName)
                .arg(HotkeyTable::fieldId)
                .arg(HotkeyTable::fieldPackage)
                .arg(HotkeyTable::fieldDescr)
                .arg(HotkeyTable::fieldSystems)))
        return q.lastError();
    return QSqlError();
}

