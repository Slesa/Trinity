#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "hotkeydialog.h"
#include "hotkeymodel.h"
#include "persist/packagetable.h"
#include "data/hotkey.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

PackageDialog::PackageDialog(QSqlRelationalTableModel* model, QWidget *parent)
  : QDialog(parent)
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
}

PackageDialog::~PackageDialog()
{
    delete _ui;
}

void PackageDialog::setData(QModelIndex index)
{
    QSqlRecord record = _model->record(index.row());

    int idIndex = _model->fieldIndex(PackageTable::fieldId);
    _editIndex = record.value(idIndex).toInt();

    int idName = _model->fieldIndex(PackageTable::fieldName);
    QString name = record.value(idName).toString();
    _ui->lineName->setText(name);

    int idDescr = _model->fieldIndex(PackageTable::fieldDescr);
    QString descr = record.value(idDescr).toString();
    _ui->textDescr->setPlainText(descr);

    this->setWindowTitle(tr("Edit package '%1'").arg(name));
}

void PackageDialog::onAddHotkey()
{
    HotkeyDialog* dlg = new HotkeyDialog(this);
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

    Hotkey hotkey = item->data(Qt::UserRole+1).value<Hotkey>();
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
    QDialog::done(r);
    emit closeMe(this);
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
