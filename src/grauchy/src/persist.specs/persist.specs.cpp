#include "persist.specs.h"
#include "persist/persist.h"
#include "persist/packagetable.h"
#include <QtTest/QtTest>


void PersistSpecs::test_database_reports_no_error()
{
    Persist persist;
    persist.setTesting();
    QSqlError sqlError = persist.initDb();
    QCOMPARE(sqlError.type(), QSqlError::NoError);
}

void PersistSpecs::test_database_can_add_package()
{
    Persist persist;
    persist.setTesting();
    persist.initDb();

    PackageTable packages;
    QSqlQuery q = packages.prepareInsertion();
    QVariant e = packages.addPackage(q, "Eins", "Mein Erstes");
    int i = e.toInt();
    QCOMPARE(i, 1);
}

/*
void CommandLineParserSpecs::rescue_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-rescue");
    bool rescue = parser.doRescue();
    QCOMPARE(rescue, true);
}

void CommandLineParserSpecs::rescue_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-r");
    bool rescue = parser.doRescue();
    QCOMPARE(rescue, true);
}

void CommandLineParserSpecs::show_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-show");
    bool show = parser.doShow();
    QCOMPARE(show, true);
}

void CommandLineParserSpecs::show_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-s");
    bool show = parser.doShow();
    QCOMPARE(show, true);
}

void CommandLineParserSpecs::options_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-options");
    bool option = parser.doOptions();
    QCOMPARE(option, true);
}

void CommandLineParserSpecs::options_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-o");
    bool option = parser.doOptions();
    QCOMPARE(option, true);
}

void CommandLineParserSpecs::multiple_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-multiple");
    bool multiple = parser.doMultiple();
    QCOMPARE(multiple, true);
}

void CommandLineParserSpecs::multiple_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-m");
    bool multiple = parser.doMultiple();
    QCOMPARE(multiple, true);
}

void CommandLineParserSpecs::exit_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-exit");
    bool exit = parser.doExit();
    QCOMPARE(exit, true);
}

void CommandLineParserSpecs::exit_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-x");
    bool exit = parser.doExit();
    QCOMPARE(exit, true);
}

void CommandLineParserSpecs::log_is_set_with_long_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-log");
    bool log = parser.doLog();
    QCOMPARE(log, true);
}

void CommandLineParserSpecs::log_is_set_with_short_arg()
{
    CommandLineParser parser;
    parser.parse(QStringList() << "-l");
    bool log = parser.doLog();
    QCOMPARE(log, true);
}

*/
