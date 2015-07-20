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
    static const char* fieldHint;

public:
    HotkeyTable();
    static QSqlQuery getAll();

    static QSqlQuery prepareInsertion();
    static int addHotkey(QSqlQuery& q, int package, const QString& descr, const QString& hint);
    static bool updateHotkey(int id, const QString& descr, const QString& hint);

    static Hotkey getFromModel(QSqlRelationalTableModel* model, int row);
    static Hotkey getById(int id);
    static QSqlQuery findById(int id);
    static QSqlQuery getForPackage(int packageId);

private:
    friend class HotkeyInitializer;
};

#endif // HOTKEYTABLE_H
