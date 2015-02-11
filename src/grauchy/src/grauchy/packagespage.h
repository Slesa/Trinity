#ifndef PACKAGESPAGE_H
#define PACKAGESPAGE_H

#include "optionspage.h"
#include <QModelIndex>

namespace Ui {
class PackagesPage;
}

class QSqlRelationalTableModel;

class PackagesPage : public OptionsPage
{
    Q_OBJECT

public:
    explicit PackagesPage(QWidget *parent = 0);
    ~PackagesPage();

    QIcon getIcon();
    QString getTitle();

private slots:
    void onPackageAdd();
    void onPackageEdit();
    void onPackageRemove();
    void onEditPackage(QModelIndex index);

    void onCurrentRowChanged(QModelIndex);

    void updateHeader(QModelIndex, int, int);
private:
    void createModel();

private:
    Ui::PackagesPage* _ui;
    QSqlRelationalTableModel* _model;
};

#endif // PACKAGESPAGE_H
