#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "data/systems.h"
#include "data/hotkey.h"

HotkeyDialog::HotkeyDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::HotkeyDialog)
{
    ui->setupUi(this);
    connect(ui->buttonStrokes, SIGNAL(clicked()), SLOT(onKeyStrokes()));
}

HotkeyDialog::~HotkeyDialog()
{
    delete ui;
}

Hotkey* HotkeyDialog::getData()
{
    Hotkey* hotkey = new Hotkey;
    hotkey->setDescription(ui->textDescription->toPlainText());

    SystemFlags systems;
    if(ui->checkLinux->isChecked()) systems |= SystemLinux;
    if(ui->checkWindows->isChecked()) systems |= SystemWindows;
    if(ui->checkMac->isChecked()) systems |= SystemMac;
    hotkey->setSystems(systems);

    QStringList tags =  ui->lineTags->text().split(',');
    hotkey->setTags(tags);

    return hotkey;
}

void HotkeyDialog::done(int r)
{
    QDialog::done(r);
    emit closeMe(this);
}

void HotkeyDialog::accept()
{
    emit takeData(this);
    QDialog::accept();
}

void HotkeyDialog::onKeyStrokes()
{
    KeyStrokeDialog* dlg = new KeyStrokeDialog(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString strokes = dlg->getKeyStrokes();
        ui->lineStrokes->setText(strokes);
    }
    delete dlg;
}
