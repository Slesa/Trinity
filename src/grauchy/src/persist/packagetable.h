#ifndef PACKAGETABLE_H
#define PACKAGETABLE_H

#include "tableinitializer.h"
#include "data/package.h"
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

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
    bool updatePackage(int id, const QString& name, const QString& descr);

    static Package getFromModel(QSqlRelationalTableModel* model, int row);
    Package getById(int id);
    QSqlQuery findById(int id);

private:
    friend class PackageInitializer;
};

#endif // PACKAGETABLE_H
