#include "hotkeydialog.h"
#include "ui_hotkeydialog.h"
#include "keystrokedialog.h"
#include "floatingdialog.h"
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
  , _package(package)
  , _editIndex(-1)
{
    _ui->setupUi(this);

    connect(_ui->buttonAllSequence, SIGNAL(clicked()), SLOT(onAllSequence()));
    connect(_ui->buttonWinSequence, SIGNAL(clicked()), SLOT(onWinSequence()));
    connect(_ui->buttonLinSequence, SIGNAL(clicked()), SLOT(onLinSequence()));
    connect(_ui->buttonMacSequence, SIGNAL(clicked()), SLOT(onMacSequence()));

    createKeyStrokeModel();

    if(package>=0)
    {
        Package pkg = PackageTable::getById(package);
        _ui->linePackage->setText(pkg.getName());
    }
}

HotkeyDialog::~HotkeyDialog()
{
    delete _ui;
}

void HotkeyDialog::setData(QModelIndex index)
{
    Hotkey hotkey;
    hotkey = HotkeyTable::getFromModel(_hotkeyModel, index.row());

    _editIndex = hotkey.getId();
    _ui->textDescription->setText(hotkey.getDescription());

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

    setWindowTitle(tr("Editing hotkey '%1'").arg(hotkey.getId()));
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
    QString descr = _ui->textDescription->toPlainText();

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

void HotkeyDialog::createKeyStrokeModel()
{
   _keyStrokeModel = new QSqlRelationalTableModel();
   _keyStrokeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
   _keyStrokeModel->setTable(KeyStrokeTable::tableName);
   int idHotkey = _keyStrokeModel->fieldIndex(KeyStrokeTable::fieldHotkey);
   _keyStrokeModel->setRelation(idHotkey, QSqlRelation(HotkeyTable::tableName, HotkeyTable::fieldId, HotkeyTable::fieldDescr));
}
