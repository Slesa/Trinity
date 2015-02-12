#ifndef HOTKEYTABLE_H
#define HOTKEYTABLE_H

#include "tableinitializer.h"
#include "data/hotkey.h"
#include <QSqlQuery>

class HotkeyTable
{
public:
    static const char* tableName;
    static const char* fieldId;
    static const char* fieldPackage;
    static const char* fieldDescr;
    static const char* fieldSystems;

public:
    HotkeyTable();

    QSqlQuery prepareInsertion();
    QVariant addHotkey(QSqlQuery& q, int package, const QString& descr, int systems);

    Hotkey getById(int id);
    QSqlQuery findById(int id);

private:
    friend class HotkeyInitializer;
};

#endif // HOTKEYTABLE_H
