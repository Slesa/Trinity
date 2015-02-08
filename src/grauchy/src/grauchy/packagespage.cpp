#include "packagespage.h"
#include "ui_packagespage.h"
#include "packagedialog.h"
#include "persist/persist.h"
#include "persist/packagetable.h"
#include <QtSql>
#include <QMessageBox>

PackagesPage::PackagesPage(QWidget *parent) :
    OptionsPage(parent),
    _ui(new Ui::PackagesPage)
{
    _ui->setupUi(this);

    _persist = new Persist;
    _persist->initDb();

    createModel();

    connect(_ui->buttonAdd, SIGNAL(clicked()), SLOT(onAdd()));
    connect(_ui->buttonEdit, SIGNAL(clicked()), SLOT(onEdit()));
    connect(_ui->buttonRemove, SIGNAL(clicked()), SLOT(onRemove()));
}

PackagesPage::~PackagesPage()
{
    delete _ui;
    delete _model;
    delete _persist;
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

void PackagesPage::onCurrentRowChanged(QModelIndex index)
{
    _ui->buttonEdit->setEnabled(index.isValid());
    _ui->buttonRemove->setEnabled(index.isValid());
}

void PackagesPage::createModel()
{
    _model = new QSqlRelationalTableModel(_ui->listPackages);
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
        showError(_model->lastError());
        return;
    }
    if(!_model->rowCount())
    {
        PackageTable packageTable;

        QSqlQuery query = packageTable.prepareInsertion();
        packageTable.addPackage(query, "Zsh", "The glorious shell");
        packageTable.addPackage(query, "Vi", "The best editor");

       _model->select();
    }

    _ui->listPackages->setModel(_model);
    _ui->listPackages->setColumnHidden(0, true);
    _ui->listPackages->resizeColumnToContents(2);

    connect(_ui->listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    _ui->listPackages->setCurrentIndex(_model->index(0,0));
}

void PackagesPage::showError(const QSqlError& error)
{
    QMessageBox::critical(this, tr("Unable to initialize database"),
                          tr("Error initializing datase: ")+error.text());
}
