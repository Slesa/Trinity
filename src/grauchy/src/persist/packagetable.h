#ifndef PACKAGETABLE_H
#define PACKAGETABLE_H

#include "tableinitializer.h"
#include "data/package.h"
#include <QSqlQuery>

class PackageTable
{
public:
    static const char* tableName;
    static const char* fieldId;
    static const char* fieldName;
    static const char* fieldDescr;

public:
    PackageTable();

    QSqlQuery prepareInsertion();
    QVariant addPackage(QSqlQuery& q, const QString& name, const QString& descr);

    Package getById(int id);
    QSqlQuery findById(int id);

private:
    friend class PackageInitializer;
};

#endif // PACKAGETABLE_H
