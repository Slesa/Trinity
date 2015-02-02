#include "packagedialog.h"
#include "ui_packagedialog.h"

PackageDialog::PackageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageDialog)
{
    ui->setupUi(this);
}

PackageDialog::~PackageDialog()
{
    delete ui;
}
