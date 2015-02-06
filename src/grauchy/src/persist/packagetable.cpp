#include "packagetable.h"
#include "sqlexception.h"
#include <QSqlQuery>
#include <QVariant>

const char* PackageTable::tableName = "packages";


PackageTable::PackageTable()
{

}

QSqlQuery PackageTable::prepareInsertion()
{
    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into packages(name, descr) values(?, ?)")))
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
    if (!q.exec(QLatin1String("create table packages(id integer primary key, name varchar, descr varchar)")))
        return q.lastError();
    return QSqlError();
}
