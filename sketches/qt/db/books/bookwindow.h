#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QtWidgets>
#include <QtSql/QSql>

class QSqlError;
class QSqlRelationalTableModel;

namespace Ui {
class BookWindow;
}

class BookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookWindow(QWidget *parent = 0);
    ~BookWindow();

private:
    void showError(const QSqlError& error);
    Ui::BookWindow* ui;
    QSqlRelationalTableModel* model;
    int authorIdx, genreIdx;
};

#endif // BOOKWINDOW_H
