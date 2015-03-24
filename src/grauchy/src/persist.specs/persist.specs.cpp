#include "persist.specs.h"
#include "persist/persist.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
#include <QtTest/QtTest>

void PersistSpecs::initTestCase()
{
    _persist = new Persist();
    _persist->setTesting();

}

void PersistSpecs::cleanupTestCase()
{
    delete _persist;
}

void PersistSpecs::test_database_reports_no_error()
{
    QSqlError sqlError = _persist->initDb();
    QCOMPARE(sqlError.type(), QSqlError::NoError);
}

void PersistSpecs::test_database_can_add_package()
{
    _persist->initDb();

    PackageTable packages;
    QSqlQuery q = packages.prepareInsertion();
    QVariant e = packages.addPackage(q, "Eins", "Mein Erstes");
    int i = e.toInt();
    QCOMPARE(i, 1);
}

void PersistSpecs::test_database_can_find_inserted_element()
{
    _persist->initDb();

    PackageTable packages;
    QSqlQuery q = packages.prepareInsertion();
    QVariant e = packages.addPackage(q, "Eins", "Mein Erstes");
    int id = e.toInt();

    QSqlQuery query = packages.findById(id);
    QCOMPARE(query.next(), true);

    int nameIdx = query.record().indexOf("name");
    QString name = query.value(nameIdx).toString();
    QCOMPARE(name, QString::fromLocal8Bit("Eins"));

    int descrIdx = query.record().indexOf("descr");
    QString descr = query.value(descrIdx).toString();
    QCOMPARE(descr, QString::fromLocal8Bit("Mein Erstes"));

    QCOMPARE(query.next(), false);
}

void PersistSpecs::test_database_can_find_inserted_package()
{
    _persist->initDb();

    PackageTable packages;
    QSqlQuery q = packages.prepareInsertion();
    QVariant e = packages.addPackage(q, "Eins", "Mein Erstes");
    int id = e.toInt();

    Package package = packages.getById(id);
    QCOMPARE(package.getId(), id);
    QCOMPARE(package.getName(), QString::fromLocal8Bit("Eins"));
    QCOMPARE(package.getDescription(), QString::fromLocal8Bit("Mein Erstes"));
}


void PersistSpecs::test_database_can_find_inserted_hotkey()
{
    _persist->initDb();

    HotkeyTable hotkeys;
    QSqlQuery q = hotkeys.prepareInsertion();
    QVariant e = hotkeys.addHotkey(q, 2, "Mein Erstes", "Sollte laufen");
    int id = e.toInt();

    Hotkey hotkey = hotkeys.getById(id);
    QCOMPARE(hotkey.getId(), id);
    QCOMPARE(hotkey.getPackage(), 2);
    QCOMPARE(hotkey.getDescription(), QString::fromLocal8Bit("Mein Erstes"));
    QCOMPARE(hotkey.getHint(), QString::fromLocal8Bit("Sollte laufen"));
}
