#ifndef PACKAGESPAGE_H
#define PACKAGESPAGE_H

#include "optionspage.h"
#include <QModelIndex>

namespace Ui {
class PackagesPage;
}

class QSqlRelationalTableModel;

//
// Options dialog, page with list of packages
//
class PackagesPage : public OptionsPage
{
    Q_OBJECT

public:
    // Create the packages page and connect all buttons to their actions
    PackagesPage(QWidget *parent = 0);

    // Destroy the gui resources
    ~PackagesPage();

    // Options page interface, get the icon for this page
    QIcon getIcon();

    // Options page interface, get the title for this page
    QString getTitle();

private slots:
    // Button action: add a new package
    void onPackageAdd();

    // Button action: edit the current package
    void onPackageEdit();

    // Button action: remove the current package
    void onPackageRemove();

    // Listview action: edit current package
    void onEditPackage(QModelIndex index);

    // Check if we have a valid index or disable index-dependant buttons otherwise
    void onCurrentRowChanged(QModelIndex);

private:
    // Fit the name column width to the largest name
    void updateHeader();
    // Create the packages database model
    void createModel();

private:
    Ui::PackagesPage* _ui;
    QSqlRelationalTableModel* _model;
};

#endif // PACKAGESPAGE_H
