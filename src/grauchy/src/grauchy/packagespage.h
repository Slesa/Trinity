#ifndef PACKAGESPAGE_H
#define PACKAGESPAGE_H

#include "optionspage.h"

namespace Ui {
class PackagesPage;
}

class PackagesPage : public OptionsPage
{
    Q_OBJECT

public:
    explicit PackagesPage(QWidget *parent = 0);
    ~PackagesPage();

    QIcon getIcon();
    QString getTitle();

private slots:
    void onAdd();
    void onEdit();
    void onRemove();

private:
    Ui::PackagesPage *ui;
};

#endif // PACKAGESPAGE_H
