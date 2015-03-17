#include "mainview.h"
#include "ui_mainview.h"
#include "optionsdialog.h"
#include "persist/persist.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
#include "persist/keystroketable.h"
#include <QApplication>
#include <QMessageBox>

// http://www.bogotobogo.com/Qt/Qt5_QListView_QStringListModel_ModelView_MVC.php

MainView::MainView(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::MainView)
    , _optionsDlg(NULL)
{
    _ui->setupUi(this);

    _persist = new Persist;
    _persist->initDb();
    createModels();

    connect(_ui->_pushQuit, SIGNAL(clicked()), SLOT(onQuit()));
    connect(_ui->_pushOptions, SIGNAL(clicked()), SLOT(onOptions()));
    connect(_ui->_lineInput, SIGNAL(textChanged(QString)), SLOT(onUpdateResult(QString)));
    connect(_ui->_comboPackages, SIGNAL(currentIndexChanged(int)), SLOT(onPackageChanged()));
}

MainView::~MainView()
{
    if(_optionsDlg) delete _optionsDlg;
    delete _searchModel;
    delete _packageModel;
    delete _persist;
    delete _ui;
}

void MainView::onPackageChanged()
{
    _currentPackage = PackageTable::getFromModel(_packageModel, _ui->_comboPackages->currentIndex());
    onUpdateResult(_ui->_lineInput->text());
}

void MainView::onUpdateResult(QString text)
{
    // Filter: only current package
    QString filter = QString("%1=%2").arg(HotkeyTable::fieldPackage).arg(_currentPackage.getId());

#if (defined Q_OS_WIN)
    int oSystem = SystemWindows;
#elif (defined Q_OS_MAC)
    int oSystem = SystemMac;
#elif (defined Q_OS_UNIX)
    int oSystem = SystemLinux;
#endif

    // Filter: only non-empty sequences
    filter += " AND ";
    filter += QString("%1<>''").arg(KeyStrokeTable::fieldSequence);

    // Filter: current or all systems
    filter += " AND ";
    filter += QString("(%1=%2 OR %1=%3)").arg(KeyStrokeTable::fieldSystem).arg(SystemAll).arg(oSystem);

    // Filter: search text
    if(!text.isEmpty())
    {
        filter += " AND ";
        filter += QString("%1 LIKE '%%2%'").arg(HotkeyTable::fieldDescr).arg(text);
    }
    _searchModel->setFilter(filter);
    _searchModel->select();
}

void MainView::onOptions()
{
    if(_optionsDlg==NULL)
    {
        _optionsDlg = new OptionsDialog(this);
        connect(_optionsDlg, SIGNAL(closeMe(QDialog*)), SLOT(closeOptions()));
    }
    _optionsDlg->show();
}

void MainView::onQuit()
{
    qApp->quit();
}

void MainView::updateData()
{
    _packageModel->select();
    _ui->_comboPackages->setCurrentIndex(0);
}

void MainView::closeOptions()
{
    _optionsDlg = NULL;
    updateData();
}

void MainView::createModels()
{
    createPackageModel();
    createSearchModel();
}

void MainView::createSearchModel()
{
    _searchModel = new QSqlRelationalTableModel(_ui->_listResult);
    _searchModel->setTable(KeyStrokeTable::tableName);

    _ui->_listResult->setModel(_searchModel);

    int idIndex = _searchModel->fieldIndex(KeyStrokeTable::fieldId);
    _searchModel->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
    int idHotkey = _searchModel->fieldIndex(KeyStrokeTable::fieldHotkey);
    _searchModel->setRelation(idHotkey, QSqlRelation(HotkeyTable::tableName, HotkeyTable::fieldId, HotkeyTable::fieldDescr));
    _searchModel->setHeaderData(idHotkey, Qt::Horizontal, tr("Description"));
    int idSequence = _searchModel->fieldIndex(KeyStrokeTable::fieldSequence);
    _searchModel->setHeaderData(idSequence, Qt::Horizontal, tr("Sequence"));
    int idSystem = _searchModel->fieldIndex(KeyStrokeTable::fieldSystem);
    _searchModel->setHeaderData(idSystem, Qt::Horizontal, tr("System"));
    _ui->_listResult->setColumnHidden(idIndex, true);
    _ui->_listResult->setColumnHidden(idSystem, true);
    _ui->_listResult->horizontalHeader()->setSectionResizeMode(idHotkey, QHeaderView::Stretch);
}

void MainView::createPackageModel()
{
    _packageModel = new QSqlRelationalTableModel(_ui->_comboPackages);
    _packageModel->setTable(PackageTable::tableName);

    if(!_packageModel->select())
    {
        showError(_packageModel->lastError());
        return;
    }
    if(!_packageModel->rowCount())
    {
        createDemoData();
    }

    _ui->_comboPackages->setModel(_packageModel);
    _ui->_comboPackages->setModelColumn(1);

    updateData();
}

void MainView::createDemoData()
{
    PackageTable packageTable;
    QSqlQuery query = packageTable.prepareInsertion();
    int rsIdx = packageTable.addPackage(query, "Resharper", "Visual Studio Extension").toInt();
    int vsIdx = packageTable.addPackage(query, "Visual Studio", "Visual Studio").toInt();
    int zshIdx = packageTable.addPackage(query, "Zsh", "The glorious shell").toInt();
    int viIdx = packageTable.addPackage(query, "Vi", "The best editor").toInt();

    HotkeyTable hotkeyTable;
    query = hotkeyTable.prepareInsertion();
    int zshStartLine = hotkeyTable.addHotkey(query, zshIdx, "Goto start of line").toInt();
    int zshEndLine = hotkeyTable.addHotkey(query, zshIdx, "Goto end of line").toInt();
    int viStartLine = hotkeyTable.addHotkey(query, viIdx, "Goto start of line").toInt();
    int viEndLine = hotkeyTable.addHotkey(query, viIdx, "Goto end of line").toInt();
    int viStartDoc = hotkeyTable.addHotkey(query, viIdx, "Goto start of document").toInt();
    int viEndDoc = hotkeyTable.addHotkey(query, viIdx, "Goto end of document").toInt();

    KeyStrokeTable keyStrokeTable;
    query = keyStrokeTable.prepareInsertion();
    keyStrokeTable.addKeyStroke(query, zshStartLine, "Ctrl+a", SystemAll);
    keyStrokeTable.addKeyStroke(query, zshEndLine, "Ctrl+e", SystemAll);
    keyStrokeTable.addKeyStroke(query, viStartLine, "^", SystemAll);
    keyStrokeTable.addKeyStroke(query, viEndLine, "$", SystemAll);
    keyStrokeTable.addKeyStroke(query, viStartDoc, "gg", SystemAll);
    keyStrokeTable.addKeyStroke(query, viEndDoc, "G", SystemAll);
}

void MainView::showError(const QSqlError& error)
{
    QMessageBox::critical(this, tr("Unable to initialize database"),
                          tr("Error initializing datase: ")+error.text());
}


