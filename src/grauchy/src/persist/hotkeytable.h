#ifndef HOTKEYTABLE_H
#define HOTKEYTABLE_H

#include "tableinitializer.h"
#include "data/hotkey.h"
#include <QSqlQuery>

class QSqlRelationalTableModel;

class HotkeyTable
{
public:
    static const char* tableName;
    static const char* fieldId;
    static const char* fieldPackage;
    static const char* fieldDescr;

public:
    HotkeyTable();
    static QSqlQuery getAll();

    QSqlQuery prepareInsertion();
    QVariant addHotkey(QSqlQuery& q, int package, const QString& descr);
    bool updateHotkey(int id, const QString& descr);

    static Hotkey getFromModel(QSqlRelationalTableModel* model, int row);
    static Hotkey getById(int id);
    static QSqlQuery findById(int id);

private:
    friend class HotkeyInitializer;
};

#endif // HOTKEYTABLE_H
