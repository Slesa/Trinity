#include "sqlexception.h"

SqlException::SqlException(const QSqlError& sqlError)
    : _sqlError(sqlError)
{
}
