#include "keystroketable.h"
#include "sqlexception.h"
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

const char* KeyStrokeTable::tableName = "keystrokes";
const char* KeyStrokeTable::fieldId = "id";
const char* KeyStrokeTable::fieldHotkey = "hotkey";
const char* KeyStrokeTable::fieldSystem = "system";
const char* KeyStrokeTable::fieldSequence = "sequence";

KeyStrokeTable::KeyStrokeTable()
{
}

QSqlQuery KeyStrokeTable::prepareInsertion()
{
    QSqlQuery q;
    if(!q.prepare(QString("insert into %1(%2, %3, %4) values(?, ?, ?)")
                  .arg(tableName)
                  .arg(fieldHotkey)
                  .arg(fieldSequence)
                  .arg(fieldSystem)))
        throw new SqlException(q.lastError());
    return q;
}

QVariant KeyStrokeTable::addKeyStroke(QSqlQuery& q, int hotkey, const QString& sequence, int system)
{
    q.addBindValue(hotkey);
    q.addBindValue(sequence);
    q.addBindValue(system);
    q.exec();
    return q.lastInsertId();
}

bool KeyStrokeTable::updateKeyStroke(int id, const QString& sequence, int system)
{
    QSqlQuery q;
    QString cmd = QString("update %1 set %2='%3', %4='%5' where %6='%7'")
            .arg(tableName)
            .arg(fieldSequence)
            .arg(sequence)
            .arg(fieldSystem)
            .arg(system)
            .arg(fieldId)
            .arg(id);
    bool ok = q.exec(cmd);
    if(!ok)
        qDebug() << "Unable to update " << id << ": " << q.lastError();
    return ok;
}

KeyStroke KeyStrokeTable::getFromModel(QSqlRelationalTableModel* model, int row)
{
    KeyStroke keyStroke;
    QSqlRecord record = model->record(row);

    int idIndex = model->fieldIndex(KeyStrokeTable::fieldId);
    keyStroke.setId(record.value(idIndex).toInt());

    int hotkeyIdx = model->fieldIndex(KeyStrokeTable::fieldHotkey);
    keyStroke.setHotkey(record.value(hotkeyIdx).toInt());

    int sequenceIdx = model->fieldIndex(KeyStrokeTable::fieldSequence);
    keyStroke.setSequence(record.value(sequenceIdx).toString());

    int systemIdx = model->fieldIndex(KeyStrokeTable::fieldSystem);
    keyStroke.setSystem(record.value(systemIdx).toInt());

    return keyStroke;
}

KeyStroke KeyStrokeTable::getById(int id)
{
    KeyStroke keyStroke;

    QSqlQuery query = findById(id);
    if(!query.next())
        return keyStroke;

    keyStroke.setId(id);

    int hotkeyIdx = query.record().indexOf(fieldHotkey);
    int hotkey = query.value(hotkeyIdx).toInt();
    keyStroke.setHotkey(hotkey);

    int sequenceIdx = query.record().indexOf(fieldSequence);
    QString sequence = query.value(sequenceIdx).toString();
    keyStroke.setSequence(sequence);

    int systemIdx = query.record().indexOf(fieldSystem);
    int system = query.value(systemIdx).toInt();
    keyStroke.setSystem(system);

    return keyStroke;
}

QSqlQuery KeyStrokeTable::findById(int id)
{
    QSqlQuery query(QString("SELECT * FROM %1 WHERE %2=%3")
                    .arg(tableName)
                    .arg(fieldId)
                    .arg(id));
    return query;
}



class KeyStrokeInitializer : public TableInitializer
{
public:
    KeyStrokeInitializer();
    virtual QString getTableName();
    virtual QSqlError createTable();
};

static KeyStrokeInitializer s_keyStrokeInitializer;

KeyStrokeInitializer::KeyStrokeInitializer()
{
    TableInitializers::getInstance().doRegister(this);
}

QString KeyStrokeInitializer::getTableName()
{
    return KeyStrokeTable::tableName;
}

QSqlError KeyStrokeInitializer::createTable()
{
    QSqlQuery q;
    if (!q.exec(QString("create table %1(%2 integer primary key, %3 integer, %4 varchar, %5 integer)")
                .arg(KeyStrokeTable::tableName)
                .arg(KeyStrokeTable::fieldId)
                .arg(KeyStrokeTable::fieldHotkey)
                .arg(KeyStrokeTable::fieldSequence)
                .arg(KeyStrokeTable::fieldSystem)))
        return q.lastError();
    return QSqlError();
}

