#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "hotkeydialog.h"
#include "hotkeymodel.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
#include "data/hotkey.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

PackageDialog::PackageDialog(QSqlRelationalTableModel* model, QWidget *parent)
  : FloatingDialog(parent)
  , _ui(new Ui::PackageDialog)
  , _model(model)
  , _editIndex(-1)
{
    _ui->setupUi(this);

    connect(_ui->buttonAdd, SIGNAL(clicked()), SLOT(onAddHotkey()));
    connect(_ui->buttonEdit, SIGNAL(clicked()), SLOT(onEditHotkey()));
//    connect(ui->listHotkeys, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(onEditHotkey(QListWidgetItem*)));
//    _ui->listHotkeys->setModel(new HotkeyModel(package.getHotkeys()));
//    ui->buttonBox->button(QDialogButtonBox::Ok)->setIcon(QIcon(""));
    createHotkeyModel();
}

PackageDialog::~PackageDialog()
{
    delete _ui;
}

void PackageDialog::setData(QModelIndex index)
{
    Package package;
    package = PackageTable::getFromModel(_model, index.row());

    _editIndex = package.getId();
    _ui->lineName->setText(package.getName());
    _ui->textDescr->setPlainText(package.getDescription());

    this->setWindowTitle(tr("Edit package '%1'").arg(package.getName()));
}

void PackageDialog::onAddHotkey()
{
    HotkeyDialog* dlg = new HotkeyDialog(_hotkeyModel, this);
    connect(dlg, SIGNAL(takeData(HotkeyDialog*)), SLOT(onTakeHotkey(HotkeyDialog*)));
    openDialog(dlg);
}

void PackageDialog::onEditHotkey()
{
/*    QListWidgetItem* item = ui->listHotkeys->currentItem();
    if(!item) return;

    onEditHotkey(item);
    */
}

    /*
void PackageDialog::onEditHotkey(QListWidgetItem* item)
{
    HotkeyDialog* dlg = new HotkeyDialog(this);

    Hotkey hotkey = item->data(Qt::UserRole+1).valueHotkey>();
    dlg->setData(hotkey);

    connect(dlg, SIGNAL(takeData(HotkeyDialog*)), SLOT(onTakeHotkey(HotkeyDialog*)));
    openDialog(dlg);
}
    */

void PackageDialog::onTakeHotkey(HotkeyDialog* dlg)
{
    /*
    Hotkey hotkey = dlg->getData();
    QVariant varHotkey;
    varHotkey.setValue(hotkey);
    QListWidgetItem* item = new QListWidgetItem(ui->listHotkeys);
    item->setData(Qt::UserRole+1, varHotkey);
    item->setText(hotkey.getDescription());
*/
}

void PackageDialog::onHotkeyClosed(QDialog* dlg)
{
    _openDialogs.removeOne(dlg);
    delete dlg;
}

void PackageDialog::openDialog(QDialog* dlg)
{
    connect(dlg, SIGNAL(closeMe(QDialog*)), SLOT(onHotkeyClosed(QDialog*)));
    _openDialogs.append(dlg);
    dlg->show();
}

void PackageDialog::done(int r)
{
    foreach(QDialog* dlg, _openDialogs)
    {
        delete dlg;
    }
    FloatingDialog::done(r);
}

void PackageDialog::accept()
{
    QString name = _ui->lineName->text();
    QString descr = _ui->textDescr->toPlainText();

    PackageTable packages;
    if(_editIndex>=0)
    {
        packages.updatePackage(_editIndex, name, descr);
    }
    else
    {
        QSqlQuery query = packages.prepareInsertion();
        packages.addPackage(query, name, descr);
    }

    _model->submit();

    QDialog::accept();
}

void PackageDialog::createHotkeyModel()
{
    _hotkeyModel = new QSqlRelationalTableModel(_ui->_listHotkeys);
    _hotkeyModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    _hotkeyModel->setTable(HotkeyTable::tableName);

    connect(_hotkeyModel, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(updateHeader(QModelIndex, int, int)));
    connect(_hotkeyModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), SLOT(updateHeader(QModelIndex, int, int)));

    int idIndex = _hotkeyModel->fieldIndex(HotkeyTable::fieldId);
    _hotkeyModel->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
//    int idName = _model->fieldIndex(PackageTable::fieldName);
//    _model->setHeaderData(idName, Qt::Horizontal, tr("Name"));
//    int idDescr = _model->fieldIndex(PackageTable::fieldDescr);
//    _hotkeyModel->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));

    if(!_hotkeyModel->select())
    {
        return;
    }

    _ui->_listHotkeys->setModel(_hotkeyModel);
    _ui->_listHotkeys->setColumnHidden(0, true);
    _ui->_listHotkeys->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

//    connect(_ui->_listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    _ui->_listHotkeys->setCurrentIndex(_model->index(0,0));
}

void PackageDialog::updateHeader(QModelIndex, int, int)
{
    _ui->_listHotkeys->resizeColumnToContents(1);
}

