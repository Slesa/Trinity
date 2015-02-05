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
}

PackageDialog::~PackageDialog()
{
    delete ui;
}

void PackageDialog::done(int r)
{
    foreach(QDialog* dlg, _hotkeyDialogs)
    {
        delete dlg;
    }
    QDialog::done(r);
}

void PackageDialog::onAddHotkey()
{
    HotkeyDialog* dlg = new HotkeyDialog(this);
    connect(dlg, SIGNAL(takeData(HotkeyDialog*)), SLOT(onTakeHotkey(HotkeyDialog*)));
    connect(dlg, SIGNAL(closeMe(QDialog*)), SLOT(onHotkeyClosed(QDialog*)));
    _hotkeyDialogs.append(dlg);
    dlg->show();
}

void PackageDialog::onTakeHotkey(HotkeyDialog* dlg)
{
    Hotkey* hotkey = dlg->getData();
    QListWidgetItem* item = new QListWidgetItem(ui->listHotkeys);
    item->setText(hotkey->getDescription());

}

void PackageDialog::onHotkeyClosed(QDialog* dlg)
{
    _hotkeyDialogs.removeOne(dlg);
    delete dlg;
}
