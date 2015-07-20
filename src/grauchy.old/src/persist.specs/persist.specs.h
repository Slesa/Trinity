#ifndef PERSIST_SPECS_H
#define PERSIST_SPECS_H

#include <QObject>

class Persist;

class PersistSpecs : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_database_reports_no_error();
    void test_database_can_add_package();
    void test_database_can_find_inserted_element();
    void test_database_can_find_inserted_package();
    void test_database_can_find_inserted_hotkey();
private:
    Persist* _persist;
};

#endif
