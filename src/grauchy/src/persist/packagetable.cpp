#include "packagetable.h"
#include "hotkeytable.h"
#include "keystroketable.h"
#include "sqlexception.h"
#include "data/hotkey.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

const char* PackageTable::tableName = "packages";
const char* PackageTable::fieldId = "id";
const char* PackageTable::fieldName = "name";
const char* PackageTable::fieldDescr = "descr";


PackageTable::PackageTable()
{
}

QSqlQuery PackageTable::prepareInsertion()
{
    QSqlQuery q;
    if (!q.prepare(QString("insert into %1(%2, %3) values(?, ?)")
                   .arg(tableName)
                   .arg(fieldName)
                   .arg(fieldDescr)))
        throw new SqlException(q.lastError());
    return q;
}

int PackageTable::addPackage(QSqlQuery& q, const QString& name, const QString& descr)
{
    q.addBindValue(name);
    q.addBindValue(descr);
    q.exec();
    return q.lastInsertId().toInt();
}

bool PackageTable::updatePackage(int id, const QString& name, const QString& descr)
{
    QSqlQuery q;
    QString cmd = QString("update %1 set %2='%3', %4='%5' where id=%6")
                   .arg(tableName)
                   .arg(fieldName)
                   .arg(name)
                   .arg(fieldDescr)
                   .arg(descr)
                   .arg(id);
    bool ok = q.exec(cmd);
    if(!ok)
        qDebug() << "Unable to update " << name << ": " << q.lastError();
    return ok;
}

Package PackageTable::getFromModel(QSqlRelationalTableModel* model, int row)
{
    Package package;
    QSqlRecord record = model->record(row);

    package.setId(record.value(PackageTable::fieldId).toInt());

    QString name = record.value(PackageTable::fieldName).toString();
    package.setName(name);

    QString descr = record.value(PackageTable::fieldDescr).toString();
    package.setDescription(descr);

    return package;
}


Package PackageTable::getById(int id)
{
    Package package;

    QSqlQuery query = findById(id);
    if(!query.next())
        return package;

    package.setId(id);

    int nameIdx = query.record().indexOf(fieldName);
    QString name = query.value(nameIdx).toString();
    package.setName(name);

    int descrIdx = query.record().indexOf(fieldDescr);
    QString descr = query.value(descrIdx).toString();
    package.setDescription(descr);

    return package;
}

QSqlQuery PackageTable::findById(int id)
{
    QSqlQuery query(QString("SELECT * FROM %1 WHERE %2=%3")
                    .arg(tableName)
                    .arg(fieldId)
                    .arg(id));
    return query;
}

QString PackageTable::exportJson(QSqlRelationalTableModel* model, int row)
{
    Package package = PackageTable::getFromModel(model, row);

    QJsonObject root;
    //root[PackageTable::fieldId] = package.getId();
    root[PackageTable::fieldName] = package.getName();
    root[PackageTable::fieldDescr] = package.getDescription();

    QJsonArray jHotkeys;
    QSqlQuery hotkeyQuery = HotkeyTable::getAll();
    while(hotkeyQuery.next())
    {
        QJsonObject jHotkey;
        Hotkey hotkey = HotkeyTable::getById(hotkeyQuery.value(HotkeyTable::fieldId).toInt());
        //jHotkey[HotkeyTable::fieldId] = hotkey.getId();
        jHotkey[HotkeyTable::fieldPackage] = hotkey.getPackage();
        jHotkey[HotkeyTable::fieldDescr] = hotkey.getDescription();

        QJsonArray jKeyStrokes;
        QSqlQuery keyStrokeQuery = KeyStrokeTable::findByHotkey(hotkey.getId());
        while(keyStrokeQuery.next())
        {
            QJsonObject jKeyStroke;
            KeyStroke keyStroke = KeyStrokeTable::getById(keyStrokeQuery.value(KeyStrokeTable::fieldId).toInt());
            //jKeyStroke[KeyStrokeTable::fieldId] = keyStroke.getId();
            jKeyStroke[KeyStrokeTable::fieldHotkey] = keyStroke.getHotkey();
            jKeyStroke[KeyStrokeTable::fieldSystem] = keyStroke.getSystem();
            jKeyStroke[KeyStrokeTable::fieldSequence] = keyStroke.getSequence();
            jKeyStrokes.append(jKeyStroke);
        }
        jHotkey[KeyStrokeTable::tableName] = jKeyStrokes;

        jHotkeys.append(jHotkey);
    }
    root[HotkeyTable::tableName] = jHotkeys;

    QString json = QJsonDocument(root).toJson(QJsonDocument::Indented);
    return json;
}

QString PackageTable::importJson(const QByteArray& json)
{
    QJsonParseError jerror;
    QJsonDocument jdoc= QJsonDocument::fromJson(json, &jerror);
    if(jerror.error != QJsonParseError::NoError)
        return jerror.errorString();

    QSqlQuery query = PackageTable::prepareInsertion();

    QJsonObject root = jdoc.object();
    QString name = root[PackageTable::fieldName].toString();
    QString descr = root[PackageTable::fieldDescr].toString();
    int packageId = PackageTable::addPackage(query, name, descr);

    QJsonArray jHotkeys = root[HotkeyTable::tableName].toArray();
    foreach(QJsonValue jHotkey, jHotkeys)
    {
        const QJsonObject& hotkey = jHotkey.toObject();
        QSqlQuery hotkeyQuery = HotkeyTable::prepareInsertion();
        QString descr = hotkey[HotkeyTable::fieldDescr].toString();
        int hotkeyId = HotkeyTable::addHotkey(hotkeyQuery, packageId, descr);
    }

    return QString::null;
}



class PackageInitializer : public TableInitializer
{
public:
    PackageInitializer();
    virtual QString getTableName();
    virtual QSqlError createTable();
};

static PackageInitializer s_packageInitializer;

PackageInitializer::PackageInitializer()
{
    TableInitializers::getInstance().doRegister(this);
}

QString PackageInitializer::getTableName()
{
    return PackageTable::tableName;
}

QSqlError PackageInitializer::createTable()
{
    QSqlQuery q;
    if (!q.exec(QString("create table %1(%2 integer primary key, %3 varchar, %4 varchar)")
                .arg(PackageTable::tableName)
                .arg(PackageTable::fieldId)
                .arg(PackageTable::fieldName)
                .arg(PackageTable::fieldDescr)))
        return q.lastError();
    return QSqlError();
}
