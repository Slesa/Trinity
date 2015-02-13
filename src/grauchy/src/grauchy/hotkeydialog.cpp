#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "floatingdialog.h"
#include "data/systems.h"
#include "persist/hotkeytable.h"
#include <QSqlRelationalTableModel>

HotkeyDialog::HotkeyDialog(int package, QSqlRelationalTableModel* hotkeyModel, QWidget *parent)
  : FloatingDialog(parent)
  , ui(new Ui::HotkeyDialog)
  , _hotkeyModel(hotkeyModel)
  , _package(package)
  , _editIndex(-1)
{
    ui->setupUi(this);
    connect(ui->buttonStrokes, SIGNAL(clicked()), SLOT(onKeyStrokes()));
}

HotkeyDialog::~HotkeyDialog()
{
    delete ui;
}

void HotkeyDialog::setData(QModelIndex index)
{
    Hotkey hotkey;
    hotkey = HotkeyTable::getFromModel(_hotkeyModel, index.row());

    _editIndex = hotkey.getId();
    ui->textDescription->setText(hotkey.getDescription());
    SystemFlags systems = hotkey.getSystems();
    ui->checkLinux->setChecked(systems&SystemLinux);
    ui->checkWindows->setChecked(systems&SystemWindows);
    ui->checkMac->setChecked(systems&SystemMac);
    ui->lineTags->setText(hotkey.getTags().join(','));

    setWindowTitle(tr("Editing hotkey '%1'").arg(hotkey.getId()));
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
    QString descr = ui->textDescription->toPlainText();

    SystemFlags systems;
    if(ui->checkLinux->isChecked()) systems |= SystemLinux;
    if(ui->checkWindows->isChecked()) systems |= SystemWindows;
    if(ui->checkMac->isChecked()) systems |= SystemMac;

    QStringList tags =  ui->lineTags->text().split(',');
//    hotkey.setTags(tags);

    HotkeyTable hotkeys;
    if(_editIndex>=0)
    {
        hotkeys.updateHotkey(_editIndex, descr, systems);
    }
    else
    {
        QSqlQuery query = hotkeys.prepareInsertion();
        hotkeys.addHotkey(query, _package, descr, systems);
    }
    _hotkeyModel->submit();
    QDialog::accept();
}
