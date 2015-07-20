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
const char* HotkeyTable::fieldHint = "hint";


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
                   .arg(fieldHint)))
        throw new SqlException(q.lastError());
    return q;
}

int HotkeyTable::addHotkey(QSqlQuery& q, int package, const QString& descr, const QString& hint)
{
    q.addBindValue(package);
    q.addBindValue(descr);
    q.addBindValue(hint);
    q.exec();
    return q.lastInsertId().toInt();
}

bool HotkeyTable::updateHotkey(int id, const QString& descr, const QString& hint)
{
    QSqlQuery q;
    QString cmd = QString("update %1 set %2='%3', %4='%5' where %6=%7")
            .arg(tableName)
            .arg(fieldDescr)
            .arg(descr)
            .arg(fieldHint)
            .arg(hint)
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

    int hintIdx = model->fieldIndex(HotkeyTable::fieldHint);
    hotkey.setHint(record.value(hintIdx).toString());

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

    int hintIdx = query.record().indexOf(fieldHint);
    QString hint = query.value(hintIdx).toString();
    hotkey.setHint(hint);

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

QSqlQuery HotkeyTable::getForPackage(int packageId)
{
    QSqlQuery query(QString("SELECT * FROM %1 WHERE %2=%3")
                    .arg(tableName)
                    .arg(fieldPackage)
                    .arg(packageId));
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
                .arg(HotkeyTable::fieldHint)))
        return q.lastError();
    return QSqlError();
}

