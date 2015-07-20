#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "floatingdialog.h"
#include "resources.h"
#include "data/systems.h"
#include "data/package.h"
#include "persist/hotkeytable.h"
#include "persist/keystroketable.h"
#include "persist/packagetable.h"
#include <QSqlRelationalTableModel>

HotkeyDialog::HotkeyDialog(int package, QSqlRelationalTableModel* hotkeyModel, QWidget *parent)
  : FloatingDialog(parent)
  , _ui(new Ui::HotkeyDialog)
  , _hotkeyModel(hotkeyModel)
  , _packageId(package)
  , _editedHotkeyId(-1)
{
    this->setWindowIcon(Resources::iconHotkey());
    _ui->setupUi(this);

    connect(_ui->buttonAllSequence, SIGNAL(clicked()), SLOT(onAllSequence()));
    connect(_ui->buttonWinSequence, SIGNAL(clicked()), SLOT(onWinSequence()));
    connect(_ui->buttonLinSequence, SIGNAL(clicked()), SLOT(onLinSequence()));
    connect(_ui->buttonMacSequence, SIGNAL(clicked()), SLOT(onMacSequence()));

    connect(_ui->lineDescription, SIGNAL(textChanged(QString)), SLOT(gotChanges()));
    connect(_ui->textHint, SIGNAL(textChanged()), SLOT(gotChanges()));
    connect(_ui->lineAllSequence, SIGNAL(textChanged(QString)), SLOT(gotChanges()));
    connect(_ui->lineWinSequence, SIGNAL(textChanged(QString)), SLOT(gotChanges()));
    connect(_ui->lineLinSequence, SIGNAL(textChanged(QString)), SLOT(gotChanges()));
    connect(_ui->lineMacSequence, SIGNAL(textChanged(QString)), SLOT(gotChanges()));

    if(package>=0)
    {
        Package pkg = PackageTable::getById(package);
        _ui->linePackage->setText(pkg.getName());
    }

    noChanges();
}

HotkeyDialog::~HotkeyDialog()
{
    delete _ui;
}

void HotkeyDialog::setData(QModelIndex index)
{
    Hotkey hotkey;
    hotkey = HotkeyTable::getFromModel(_hotkeyModel, index.row());

    _editedHotkeyId = hotkey.getId();
    _ui->lineDescription->setText(hotkey.getDescription());
    _ui->textHint->setText(hotkey.getHint());

    int hotkeyId = hotkey.getId();
    KeyStrokeTable keyStrokeTable;
    QString allSequence = keyStrokeTable.getByHotkey(hotkeyId, SystemAll).getSequence();
    _ui->lineAllSequence->setText(allSequence);
    QString winSequence = keyStrokeTable.getByHotkey(hotkeyId, SystemWindows).getSequence();
    _ui->lineWinSequence->setText(winSequence);
    QString macSequence = keyStrokeTable.getByHotkey(hotkeyId, SystemMac).getSequence();
    _ui->lineMacSequence->setText(macSequence);
    QString linSequence = keyStrokeTable.getByHotkey(hotkeyId, SystemLinux).getSequence();
    _ui->lineLinSequence->setText(linSequence);

    setWindowTitle(tr("Editing hotkey '%1'").arg(hotkey.getDescription()));
}

void HotkeyDialog::onAllSequence()
{
    onSequence(_ui->lineAllSequence);
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
    QString descr = _ui->lineDescription->text();
    QString hint = _ui->textHint->toPlainText();

    HotkeyTable hotkeys;
    if(_editedHotkeyId>=0)
    {
        hotkeys.updateHotkey(_editedHotkeyId, descr, hint);
        KeyStrokeTable::addOrUpdateKeyStroke(_editedHotkeyId, SystemAll, _ui->lineAllSequence->text());
        KeyStrokeTable::addOrUpdateKeyStroke(_editedHotkeyId, SystemWindows, _ui->lineWinSequence->text());
        KeyStrokeTable::addOrUpdateKeyStroke(_editedHotkeyId, SystemLinux, _ui->lineLinSequence->text());
        KeyStrokeTable::addOrUpdateKeyStroke(_editedHotkeyId, SystemMac, _ui->lineMacSequence->text());
    }
    else
    {
        QSqlQuery query = hotkeys.prepareInsertion();
        hotkeys.addHotkey(query, _packageId, descr, hint);
    }
    _hotkeyModel->submit();
    QDialog::accept();
}

void HotkeyDialog::noChanges()
{
    _ui->buttonBox->setStandardButtons(QDialogButtonBox::Close);
    _ui->buttonBox->button(QDialogButtonBox::Close)->setIcon(Resources::iconClose());
}

void HotkeyDialog::gotChanges()
{
    _ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    _ui->buttonBox->button(QDialogButtonBox::Ok)->setIcon(Resources::iconOk());
    _ui->buttonBox->button(QDialogButtonBox::Cancel)->setIcon(Resources::iconCancel());
}
