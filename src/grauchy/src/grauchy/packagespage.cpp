#include "packagespage.h"
#include "ui_packagespage.h"
#include "packagedialog.h"
#include "persist/packagetable.h"
#include <QtSql>

PackagesPage::PackagesPage(QWidget *parent) :
    OptionsPage(parent),
    _ui(new Ui::PackagesPage)
{
    _ui->setupUi(this);

    createModel();

    connect(_ui->_listPackages, SIGNAL(doubleClicked(QModelIndex)), SLOT(onPackageEdit(QModelindex)));
    connect(_ui->_buttonAdd, SIGNAL(clicked()), SLOT(onAdd()));
    connect(_ui->_buttonEdit, SIGNAL(clicked()), SLOT(onEdit()));
    connect(_ui->_buttonRemove, SIGNAL(clicked()), SLOT(onRemove()));
}

PackagesPage::~PackagesPage()
{
    delete _ui;
    delete _model;
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

void PackagesPage::onPackageEdit(QModelIndex index)
{

}

void PackagesPage::onCurrentRowChanged(QModelIndex index)
{
    _ui->_buttonEdit->setEnabled(index.isValid());
    _ui->_buttonRemove->setEnabled(index.isValid());
}

void PackagesPage::createModel()
{
    _model = new QSqlRelationalTableModel(_ui->_listPackages);
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    _model->setTable(PackageTable::tableName);

    int idIndex = _model->fieldIndex(PackageTable::fieldId);
    _model->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
    int idName = _model->fieldIndex(PackageTable::fieldName);
    _model->setHeaderData(idName, Qt::Horizontal, tr("Name"));
    int idDescr = _model->fieldIndex(PackageTable::fieldDescr);
    _model->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));

    if(!_model->select())
    {
        return;
    }

    _ui->_listPackages->setModel(_model);
    _ui->_listPackages->setColumnHidden(0, true);
    _ui->_listPackages->resizeColumnToContents(2);

    connect(_ui->_listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    _ui->_listPackages->setCurrentIndex(_model->index(0,0));
}
