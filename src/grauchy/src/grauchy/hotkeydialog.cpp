#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "floatingdialog.h"
#include "data/systems.h"
#include "persist/hotkeytable.h"
#include <QSqlRelationalTableModel>

HotkeyDialog::HotkeyDialog(int package, QSqlRelationalTableModel* hotkeyModel, QWidget *parent)
  : FloatingDialog(parent)
  , _ui(new Ui::HotkeyDialog)
  , _hotkeyModel(hotkeyModel)
  , _package(package)
  , _editIndex(-1)
{
    _ui->setupUi(this);
    connect(_ui->buttonWinSequence, SIGNAL(clicked()), SLOT(onWinSequence()));
    connect(_ui->buttonLinSequence, SIGNAL(clicked()), SLOT(onLinSequence()));
    connect(_ui->buttonMacSequence, SIGNAL(clicked()), SLOT(onMacSequence()));
}

HotkeyDialog::~HotkeyDialog()
{
    delete _ui;
}

void HotkeyDialog::setData(QModelIndex index, const QString& packageName)
{
    Hotkey hotkey;
    hotkey = HotkeyTable::getFromModel(_hotkeyModel, index.row());

    _editIndex = hotkey.getId();
    _ui->textDescription->setText(hotkey.getDescription());
    /*
    SystemFlags systems = hotkey.getSystems();
    _ui->checkLinux->setChecked(systems&SystemLinux);
    _ui->checkWindows->setChecked(systems&SystemWindows);
    _ui->checkMac->setChecked(systems&SystemMac);
    _ui->lineTags->setText(hotkey.getTags().join(','));
    */
    _ui->linePackage->setText(packageName);

    setWindowTitle(tr("Editing hotkey '%1'").arg(hotkey.getId()));
}

void HotkeyDialog::onWinSequence()
{
    onSequence(_ui->lineWinSequence);
}

void HotkeyDialog::onLinSequence()
{
    onSequence(_ui->lineLinSequence);
}

void HotkeyDialog::onMacSequence()
{
    onSequence(_ui->lineMacSequence);
}

void HotkeyDialog::onSequence(QLineEdit* lineEdit)
{
    KeyStrokeDialog* dlg = new KeyStrokeDialog(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString strokes = dlg->getKeyStrokes();
        lineEdit->setText(strokes);
    }
    delete dlg;
}

void HotkeyDialog::accept()
{
    QString descr = _ui->textDescription->toPlainText();

    //SystemFlags systems;
    //if(_ui->checkLinux->isChecked()) systems |= SystemLinux;
    //if(_ui->checkWindows->isChecked()) systems |= SystemWindows;
    //if(_ui->checkMac->isChecked()) systems |= SystemMac;

    //QStringList tags =  _ui->lineTags->text().split(',');
//    hotkey.setTags(tags);

    HotkeyTable hotkeys;
    if(_editIndex>=0)
    {
        hotkeys.updateHotkey(_editIndex, descr);
    }
    else
    {
        QSqlQuery query = hotkeys.prepareInsertion();
        hotkeys.addHotkey(query, _package, descr);
    }
    _hotkeyModel->submit();
    QDialog::accept();
}
