#ifndef PERSIST_H
#define PERSIST_H

#include <QtSql>

class Persist
{
    static const char* DatabaseName;
    static const char* DatabaseTest;
public:
    Persist();

    void setTesting() { _testing = true; }
    QSqlError initDb();

private:
    QSqlDatabase _db;
    bool _testing;
};

#endif // PERSIST_H
