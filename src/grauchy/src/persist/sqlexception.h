#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <QSqlError>

class SqlException
{
public:
    SqlException(const QSqlError& sqlError);
private:
    QSqlError _sqlError;
};

#endif // SQLEXCEPTION_H
