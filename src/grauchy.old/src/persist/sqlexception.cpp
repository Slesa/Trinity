#include "sqlexception.h"
#include <QSqlError>
#include <QDebug>

SqlException::SqlException(const QSqlError& sqlError)
    : _sqlError(sqlError)
{
    qDebug() << "SQL error: " << sqlError.text();
}
