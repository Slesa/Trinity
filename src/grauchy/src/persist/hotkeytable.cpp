#include "hotkeytable.h"
#include "sqlexception.h"
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

const char* HotkeyTable::tableName = "hotkeys";
const char* HotkeyTable::fieldId = "id";
const char* HotkeyTable::fieldPackage = "package";
const char* HotkeyTable::fieldDescr = "descr";


HotkeyTable::HotkeyTable()
{
}

QSqlQuery HotkeyTable::prepareInsertion()
{
    QSqlQuery q;
    if (!q.prepare(QString("insert into %1(%2, %3) values(?, ?)")
                   .arg(tableName)
                   .arg(fieldPackage)
                   .arg(fieldDescr)))
        throw new SqlException(q.lastError());
    return q;
}

int HotkeyTable::addHotkey(QSqlQuery& q, int package, const QString& descr)
{
    q.addBindValue(package);
    q.addBindValue(descr);
    q.exec();
    return q.lastInsertId().toInt();
}

bool HotkeyTable::updateHotkey(int id, const QString& descr)
{
    QSqlQuery q;
    QString cmd = QString("update %1 set %2='%3' where %4=%5")
            .arg(tableName)
            .arg(fieldDescr)
            .arg(descr)
            .arg(fieldId)
            .arg(id);
    bool ok = q.exec(cmd);
    if(!ok)
        qDebug() << "Unable to update " << id << ": " << q.lastError();
    return ok;
}

Hotkey HotkeyTable::getFromModel(QSqlRelationalTableModel* model, int row)
{
    Hotkey hotkey;
    QSqlRecord record = model->record(row);

    int idIndex = model->fieldIndex(HotkeyTable::fieldId);
    hotkey.setId(record.value(idIndex).toInt());

    int packageIdx = model->fieldIndex(HotkeyTable::fieldPackage);
    hotkey.setPackage(record.value(packageIdx).toInt());

    int descrIdx = model->fieldIndex(HotkeyTable::fieldDescr);
    hotkey.setDescription(record.value(descrIdx).toString());

    return hotkey;
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

    return hotkey;
}

QSqlQuery HotkeyTable::getAll()
{
    QSqlQuery query(QString("SELECT * FROM %1").arg(tableName));
    return query;
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
    if (!q.exec(QString("create table %1(%2 integer primary key, %3 integer, %4 varchar)")
                .arg(HotkeyTable::tableName)
                .arg(HotkeyTable::fieldId)
                .arg(HotkeyTable::fieldPackage)
                .arg(HotkeyTable::fieldDescr)))
        return q.lastError();
    return QSqlError();
}

