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

    static QSqlQuery prepareInsertion();
    static QVariant addPackage(QSqlQuery& q, const QString& name, const QString& descr);
    static bool updatePackage(int id, const QString& name, const QString& descr);

    static Package getFromModel(QSqlRelationalTableModel* model, int row);
    static Package getById(int id);
    static QSqlQuery findById(int id);

    static QString exportJson(QSqlRelationalTableModel* model, int row);

private:
    friend class PackageInitializer;
};

#endif // PACKAGETABLE_H
