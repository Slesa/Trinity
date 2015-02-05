#include "packagedialog.h"
#include "ui_packagedialog.h"
#include "hotkeydialog.h"
#include "data/hotkey.h"

PackageDialog::PackageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageDialog)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, SIGNAL(clicked()), SLOT(onAddHotkey()));
    connect(ui->buttonEdit, SIGNAL(clicked()), SLOT(onEditHotkey()));
}

PackageDialog::~PackageDialog()
{
    delete ui;
}

void PackageDialog::done(int r)
{
    foreach(QDialog* dlg, _openDialogs)
    {
        delete dlg;
    }
    QDialog::done(r);
}

void PackageDialog::onAddHotkey()
{
    HotkeyDialog* dlg = new HotkeyDialog(this);
    connect(dlg, SIGNAL(takeData(HotkeyDialog*)), SLOT(onTakeHotkey(HotkeyDialog*)));
    openDialog(dlg);
}

void PackageDialog::onEditHotkey()
{
    HotkeyDialog* dlg = new HotkeyDialog(this);

    QListWidgetItem* item = ui->listHotkeys->currentItem();
    if(!item) return;

    Hotkey* hotkey = reinterpret_cast<Hotkey*>(item->data(Qt::UserRole+1).toInt());
    dlg->setData(hotkey);

    connect(dlg, SIGNAL(takeData(HotkeyDialog*)), SLOT(onTakeHotkey(HotkeyDialog*)));
    openDialog(dlg);
}

void PackageDialog::onTakeHotkey(HotkeyDialog* dlg)
{
    Hotkey* hotkey = dlg->getData();
    QListWidgetItem* item = new QListWidgetItem(ui->listHotkeys);
    item->setData(Qt::UserRole+1, reinterpret_cast<int>(hotkey));
    item->setText(hotkey->getDescription());

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
