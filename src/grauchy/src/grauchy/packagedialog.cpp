#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "hotkeydialog.h"
#include "hotkeymodel.h"
#include "resources.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
#include "data/hotkey.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>

PackageDialog::PackageDialog(QSqlRelationalTableModel* model, QWidget *parent)
  : FloatingDialog(parent)
  , _ui(new Ui::PackageDialog)
  , _model(model)
  , _editIndex(-1)
{
    _ui->setupUi(this);

    connect(_ui->_listHotkeys, SIGNAL(activated(QModelIndex)), SLOT(onHotkeyEdit(QModelIndex)));
    connect(_ui->buttonAdd, SIGNAL(clicked()), SLOT(onHotkeyAdd()));
    connect(_ui->buttonEdit, SIGNAL(clicked()), SLOT(onHotkeyEdit()));
    connect(_ui->buttonRemove, SIGNAL(clicked()), SLOT(onHotkeyRemove()));
    connect(_ui->lineName, SIGNAL(textChanged(QString)), SLOT(gotChanges()));
    connect(_ui->textDescr, SIGNAL(textChanged()), SLOT(gotChanges()));
}

PackageDialog::~PackageDialog()
{
    delete _ui;
}

void PackageDialog::setData(QModelIndex index)
{
    createHotkeyModel();

    Package package;
    package = PackageTable::getFromModel(_model, index.row());

    _editIndex = package.getId();
    _ui->lineName->setText(package.getName());
    _ui->textDescr->setPlainText(package.getDescription());
    _ui->buttonAdd->setEnabled(true);

    _hotkeyModel->setFilter(QString("%1=%2").arg(HotkeyTable::fieldPackage).arg(_editIndex));
    _hotkeyModel->select();

    this->setWindowTitle(tr("Edit package '%1'").arg(package.getName()));
    noChanges();
}

void PackageDialog::onHotkeyAdd()
{
    HotkeyDialog* dlg = new HotkeyDialog(_editIndex, _hotkeyModel, this); // We do not have the package id yet
    if(dlg->exec()==QDialog::Accepted)
    {
        _hotkeyModel->select();
        _ui->_listHotkeys->scrollToBottom();
    }
    delete dlg;
}

void PackageDialog::onHotkeyEdit()
{
    QModelIndex index = _ui->_listHotkeys->currentIndex();
    onHotkeyEdit(index);
}

void PackageDialog::onHotkeyEdit(QModelIndex index)
{
    HotkeyDialog* dlg = new HotkeyDialog(_editIndex, _hotkeyModel, this);
    dlg->setData(index);
    if(dlg->exec()==QDialog::Accepted)
    {
        _hotkeyModel->select();
        _ui->_listHotkeys->scrollToBottom();
    }
    delete dlg;
}

void PackageDialog::onHotkeyRemove()
{
    QModelIndex index = _ui->_listHotkeys->currentIndex();
    Hotkey hotkey = HotkeyTable::getFromModel(_hotkeyModel, index.row());

    QMessageBox msg(this);
    msg.setWindowIcon(Resources::iconHotkey());
    msg.setWindowTitle(tr("Remove hotkey?"));
    msg.setInformativeText(tr("Are you sure to delete hotkey with description\n'%2'?").arg(hotkey.getDescription()));
    msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    msg.setIcon(QMessageBox::Warning);
    int button = msg.exec();
    if(button!=QMessageBox::Yes) return;

    bool ok = _hotkeyModel->removeRow(index.row());
    if(!ok) {
        QMessageBox::critical(this, tr("Error"), tr("Could not remove hotkey:\n %1").arg(_hotkeyModel->lastError().text()));
        return;
    }
    _hotkeyModel->submitAll();
    onCurrentRowChanged(QModelIndex());
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

    /*
void PackageDialog::onTakeHotkey(HotkeyDialog* dlg)
{
    Hotkey hotkey = dlg->getData();
    QVariant varHotkey;
    varHotkey.setValue(hotkey);
    QListWidgetItem* item = new QListWidgetItem(ui->listHotkeys);
    item->setData(Qt::UserRole+1, varHotkey);
    item->setText(hotkey.getDescription());
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
*/
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

void PackageDialog::onCurrentRowChanged(QModelIndex index)
{
    _ui->buttonEdit->setEnabled(index.isValid());
    _ui->buttonRemove->setEnabled(index.isValid());
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
    int idDescr = _hotkeyModel->fieldIndex(HotkeyTable::fieldDescr);
    _hotkeyModel->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));
    int idPackage = _hotkeyModel->fieldIndex(HotkeyTable::fieldPackage);
    _hotkeyModel->setRelation(idPackage, QSqlRelation(PackageTable::tableName, PackageTable::fieldId, PackageTable::fieldName));

    if(!_hotkeyModel->select())
    {
        qDebug() << "Could not select hotkeys";
        return;
    }

    _ui->_listHotkeys->setModel(_hotkeyModel);
    _ui->_listHotkeys->setColumnHidden(idIndex, true);
    _ui->_listHotkeys->setColumnHidden(idPackage, true);
    _ui->_listHotkeys->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    connect(_ui->_listHotkeys->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    _ui->_listHotkeys->setCurrentIndex(_model->index(0,0));
}

void PackageDialog::updateHeader(QModelIndex, int, int)
{
    _ui->_listHotkeys->resizeColumnToContents(1);
}

void PackageDialog::noChanges()
{
    _ui->buttonBox->setStandardButtons(QDialogButtonBox::Close);
}

void PackageDialog::gotChanges()
{
    _ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
}
