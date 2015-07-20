#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "persist/packagetable.h"
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
    void onPackageChanged();
    void onUpdateResult(QString text);

private:
    void updateData();
    void createModels();
    void createPackageModel();
    void createSearchModel();
    void createDemoData();
    void showError(const QSqlError& error);

private:
    Ui::MainView* _ui;
    Persist* _persist;
    QSqlRelationalTableModel* _packageModel;
    QSqlRelationalTableModel* _searchModel;
    OptionsDialog* _optionsDlg;
    Package _currentPackage;
};

#endif // MAINVIEW_H
