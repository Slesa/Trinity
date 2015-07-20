#ifndef DEMODATA_H
#define DEMODATA_H

class PackageTable;
class QSqlQuery;

class DemoData
{
public:
    DemoData();
    void createDemoData();
    void createZshKeys(PackageTable& packageTable, QSqlQuery& queryPackage);
    void createVimKeys(PackageTable& packageTable, QSqlQuery& queryPackage);
};

#endif // DEMODATA_H
