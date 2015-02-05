#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "hotkeydialog.h"
#include "hotkeymodel.h"
#include "data/hotkey.h"

PackageDialog::PackageDialog(const Package& package, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageDialog)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, SIGNAL(clicked()), SLOT(onAddHotkey()));
    connect(ui->buttonEdit, SIGNAL(clicked()), SLOT(onEditHotkey()));
//    connect(ui->listHotkeys, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(onEditHotkey(QListWidgetItem*)));
    ui->listHotkeys->setModel(new HotkeyModel(package.getHotkeys()));
}

PackageDialog::~PackageDialog()
{
    delete ui;
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
    emit takeData(this);
    QDialog::accept();
}
