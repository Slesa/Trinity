#include "packagespage.h"
#include "ui_packagespage.h"
#include "packagedialog.h"

PackagesPage::PackagesPage(QWidget *parent) :
    OptionsPage(parent),
    ui(new Ui::PackagesPage)
{
    ui->setupUi(this);
    connect(ui->buttonAdd, SIGNAL(clicked()), SLOT(onAdd()));
    connect(ui->buttonEdit, SIGNAL(clicked()), SLOT(onEdit()));
    connect(ui->buttonRemove, SIGNAL(clicked()), SLOT(onRemove()));
}

PackagesPage::~PackagesPage()
{
    delete ui;
}

QIcon PackagesPage::getIcon()
{
    return QIcon(":/resources/package.png");
}

QString PackagesPage::getTitle()
{
    return tr("Packages");
}

void PackagesPage::onAdd()
{
    Package package;
    PackageDialog* dlg = new PackageDialog(package, this);
    if(dlg->exec()==QDialog::Accepted)
    {

    }
}

void PackagesPage::onEdit()
{

}

void PackagesPage::onRemove()
{

}

