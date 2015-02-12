#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class MainView;
}

class Persist;
class OptionsDialog;
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
    void closeOptions();

private:
    void updateData();
    void createModel();
    void showError(const QSqlError& error);

private:
    Ui::MainView* _ui;
    Persist* _persist;
    QSqlRelationalTableModel* _model;
    OptionsDialog* _optionsDlg;
};

#endif // MAINVIEW_H
