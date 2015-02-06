#ifndef PACKAGETABLE_H
#define PACKAGETABLE_H

#include "tableinitializer.h"
#include <QSqlQuery>

class PackageTable
{
    static const char* tableName;

public:
    PackageTable();

    QSqlQuery prepareInsertion();
    QVariant addPackage(QSqlQuery& q, const QString& name, const QString& descr);

private:
    friend class PackageInitializer;
};

#endif // PACKAGETABLE_H
