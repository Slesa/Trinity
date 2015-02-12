#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "floatingdialog.h"
#include "data/systems.h"
#include <QSqlRelationalTableModel>

HotkeyDialog::HotkeyDialog(QSqlRelationalTableModel* hotkeyModel, QWidget *parent)
  : FloatingDialog(parent)
  , ui(new Ui::HotkeyDialog)
  , _hotkeyModel(hotkeyModel)
{
    ui->setupUi(this);
    connect(ui->buttonStrokes, SIGNAL(clicked()), SLOT(onKeyStrokes()));
}

HotkeyDialog::~HotkeyDialog()
{
    delete ui;
}

Hotkey HotkeyDialog::getData()
{
    Hotkey hotkey;
    hotkey.setDescription(ui->textDescription->toPlainText());

    SystemFlags systems;
    if(ui->checkLinux->isChecked()) systems |= SystemLinux;
    if(ui->checkWindows->isChecked()) systems |= SystemWindows;
    if(ui->checkMac->isChecked()) systems |= SystemMac;
    hotkey.setSystems(systems);

    QStringList tags =  ui->lineTags->text().split(',');
    hotkey.setTags(tags);

    return hotkey;
}

void HotkeyDialog::setData(const Hotkey& hotkey)
{
    ui->textDescription->setText(hotkey.getDescription());
    SystemFlags systems = hotkey.getSystems();
    ui->checkLinux->setChecked(systems&SystemLinux);
    ui->checkWindows->setChecked(systems&SystemWindows);
    ui->checkMac->setChecked(systems&SystemMac);
    ui->lineTags->setText(hotkey.getTags().join(','));
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

void HotkeyDialog::accept()
{
    emit takeData(this);
    QDialog::accept();
}
