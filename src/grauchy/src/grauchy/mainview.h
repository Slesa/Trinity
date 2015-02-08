#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class MainView;
}

class Persist;
class QSqlRelationalTableModel;
class QSqlError;

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void onOptions();
    void onQuit();

private:
    void createModel();
    void showError(const QSqlError& error);

private:
    Ui::MainView* _ui;
    Persist* _persist;
    QSqlRelationalTableModel* _model;
};

#endif // MAINVIEW_H
