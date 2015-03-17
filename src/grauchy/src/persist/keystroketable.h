#ifndef KEYSTROKETABLE_H
#define KEYSTROKETABLE_H

#include "tableinitializer.h"
#include "data/keystroke.h"
#include <QSqlQuery>

class QSqlRelationalTableModel;

class KeyStrokeTable
{
public:
    static const char* tableName;
    static const char* fieldId;
    static const char* fieldHotkey;
    static const char* fieldSystem;
    static const char* fieldSequence;

public:
    KeyStrokeTable();

    static QSqlQuery prepareInsertion();
    static QVariant addKeyStroke(QSqlQuery& query, int hotkey, const QString& sequence, int system);
    static void addOrUpdateKeyStroke(int hotkey, int system, const QString& sequence);
//    bool updateKeyStroke(int id, const QString& sequence, int system);

//    static KeyStroke getFromModel(QSqlRelationalTableModel* model, int row);
    KeyStroke getByHotkey(int hotkey, int system);
    QSqlQuery findByHotkey(int hotkey, int system);
    KeyStroke getById(int id);
    QSqlQuery findById(int id);

private:
    friend class KeyStrokeInitializer;
};

#endif // KEYSTROKETABLE_H
