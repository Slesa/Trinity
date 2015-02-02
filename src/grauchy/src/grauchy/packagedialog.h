#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include <QDialog>

namespace Ui {
class PackageDialog;
}

class PackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageDialog(QWidget *parent = 0);
    ~PackageDialog();

private:
    Ui::PackageDialog *ui;
};

#endif // PACKAGEDIALOG_H
