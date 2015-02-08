#include "packagetable.h"
#include "sqlexception.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

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

QVariant PackageTable::addPackage(QSqlQuery& q, const QString& name, const QString& descr)
{
    q.addBindValue(name);
    q.addBindValue(descr);
    q.exec();
    return q.lastInsertId();
}

Package PackageTable::getById(int id)
{
    Package package;

    QSqlQuery query = findById(id);
    if(!query.next())
        return package;

    package.setId(id);

    int nameIdx = query.record().indexOf("name");
    QString name = query.value(nameIdx).toString();
    package.setName(name);

    int descrIdx = query.record().indexOf("descr");
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
