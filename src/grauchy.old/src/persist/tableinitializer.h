#ifndef TABLEINITIALIZER_H
#define TABLEINITIALIZER_H

#include <QString>
#include <QList>
#include <QSqlError>

class TableInitializer
{
public:
    TableInitializer();
    virtual QString getTableName() = 0;
    virtual QSqlError createTable() = 0;
};

class TableInitializers
{
public:
    static TableInitializers& getInstance();

    void doRegister(TableInitializer* initializer);
    QList<TableInitializer*> getInitializers();

private:
    TableInitializers();

private:
    QList<TableInitializer*> _initializers;
};

#endif // TABLEINITIALIZER_H
