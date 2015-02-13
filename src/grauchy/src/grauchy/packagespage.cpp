#include "packagespage.h"
#include "ui_packagespage.h"
#include "packagedialog.h"
#include "resources.h"
#include "persist/packagetable.h"
#include <QtSql>
#include <QMessageBox>

PackagesPage::PackagesPage(QWidget *parent) :
    OptionsPage(parent),
    _ui(new Ui::PackagesPage)
{
    _ui->setupUi(this);

    createModel();

    connect(_ui->_listPackages, SIGNAL(activated(QModelIndex)), SLOT(onEditPackage(QModelIndex)));
    connect(_ui->_buttonAdd, SIGNAL(clicked()), SLOT(onPackageAdd()));
    connect(_ui->_buttonEdit, SIGNAL(clicked()), SLOT(onPackageEdit()));
    connect(_ui->_buttonRemove, SIGNAL(clicked()), SLOT(onPackageRemove()));
}

PackagesPage::~PackagesPage()
{
    delete _ui;
    delete _model;
}

QIcon PackagesPage::getIcon()
{
    return Resources::iconPackage();
}

QString PackagesPage::getTitle()
{
    return tr("Packages");
}

void PackagesPage::onPackageAdd()
{
    PackageDialog* dlg = new PackageDialog(_model, this);
    if(dlg->exec()==QDialog::Accepted)
    {
        _model->select();
        _ui->_listPackages->scrollToBottom();
    }
    delete dlg;
}

void PackagesPage::onPackageEdit()
{
    QModelIndex index = _ui->_listPackages->currentIndex();
    onEditPackage(index);
}

void PackagesPage::onEditPackage(QModelIndex index)
{
    PackageDialog* dlg = new PackageDialog(_model, this);
    dlg->setData(index);
    if(dlg->exec()==QDialog::Accepted)
    {
        _model->select();
        _ui->_listPackages->scrollToBottom();
    }
    delete dlg;
}

void PackagesPage::onPackageRemove()
{
    QModelIndex index = _ui->_listPackages->currentIndex();
    Package package = PackageTable::getFromModel(_model, index.row());

    QMessageBox msg(this);
    msg.setWindowTitle(tr("Remove package?"));
    msg.setInformativeText(tr("Are you sure to delete package '%1'\nwith description %2?").arg(package.getName()).arg(package.getDescription()));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    msg.setIcon(QMessageBox::Warning);
    int button = msg.exec();
    if(button!=QMessageBox::Yes) return;

    bool ok = _model->removeRow(index.row());
    if(!ok)
        QMessageBox::critical(this, tr("Error"), tr("Could not remove package:\n %1").arg(_model->lastError().text()));
    _model->submitAll();
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

    connect(_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(updateHeader(QModelIndex, int, int)));
    connect(_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), SLOT(updateHeader(QModelIndex, int, int)));

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
    _ui->_listPackages->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    connect(_ui->_listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    _ui->_listPackages->setCurrentIndex(_model->index(0,0));
}

void PackagesPage::updateHeader(QModelIndex, int, int)
{
    _ui->_listPackages->resizeColumnToContents(1);
}
