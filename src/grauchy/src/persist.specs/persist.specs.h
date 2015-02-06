#ifndef PERSIST_SPECS_H
#define PERSIST_SPECS_H

#include <QObject>

class PersistSpecs : public QObject
{
    Q_OBJECT

private slots:
    void test_database_reports_no_error();
    void test_database_can_add_package();
/*
    void rescue_is_set_with_long_arg();
    void rescue_is_set_with_short_arg();
    void show_is_set_with_long_arg();
    void show_is_set_with_short_arg();
    void options_is_set_with_long_arg();
    void options_is_set_with_short_arg();
    void multiple_is_set_with_long_arg();
    void multiple_is_set_with_short_arg();
    void exit_is_set_with_long_arg();
    void exit_is_set_with_short_arg();
    void log_is_set_with_long_arg();
    void log_is_set_with_short_arg();
    */
};

#endif
