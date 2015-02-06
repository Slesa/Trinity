#include "persist.h"
#include "tableinitializer.h"

const char* Persist::DatabaseName = "grauchy.dat";
const char* Persist::DatabaseTest = ":memory:";

Persist::Persist()
{
}

QSqlError Persist::initDb()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_testing ? DatabaseTest : DatabaseName);

    if(!_db.open())
        return _db.lastError();

    QStringList tables = _db.tables();
    foreach(TableInitializer* initializer, TableInitializers::getInstance().getInitializers())
    {
        if( tables.contains(initializer->getTableName())) continue;

        QSqlError sqlError = initializer->createTable();
        if(sqlError.type()!=QSqlError::NoError) return sqlError;
    }

    return QSqlError();
}
