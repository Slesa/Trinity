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
    QString filter =  QString("%1=%2").arg(HotkeyTable::fieldPackage).arg(_currentPackage.getId());

    if(!text.isEmpty())
    {
        filter += " AND ";
        //filter += QString("LOWER(%1) LIKE %'%2'%").arg(HotkeyTable::fieldDescr).arg(text.toLower());
        filter += QString("LOWER(%1) CONTAINS %2").arg(HotkeyTable::fieldDescr).arg(text.toLower());
//        QStringList tags = text.split(' ');
//        foreach(QString tag, tags)
//        {
//            filter += QString('')
//        }
    }
    _searchModel->setFilter(filter);
//    _searchModel->setFilter(QString("%0 like '%1'").arg(HotkeyTable::fieldDescr).arg(filter));
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
    _searchModel->setTable(HotkeyTable::tableName);
    _ui->_listResult->setModel(_searchModel);


    int idIndex = _searchModel->fieldIndex(HotkeyTable::fieldId);
    _searchModel->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
    int idPackage = _searchModel->fieldIndex(HotkeyTable::fieldPackage);
    _searchModel->setHeaderData(idPackage, Qt::Horizontal, tr("Package"));
    int idDescr = _searchModel->fieldIndex(HotkeyTable::fieldDescr);
    _searchModel->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));
    _ui->_listResult->setColumnHidden(idIndex, true);
    _ui->_listResult->setColumnHidden(idPackage, true);
    _ui->_listResult->horizontalHeader()->setSectionResizeMode(idDescr, QHeaderView::Stretch);
}

void MainView::createPackageModel()
{
    _packageModel = new QSqlRelationalTableModel(_ui->_comboPackages);
    _packageModel->setTable(PackageTable::tableName);
/*
    int idIndex = _model->fieldIndex(PackageTable::fieldId);
    _model->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
    int idName = _model->fieldIndex(PackageTable::fieldName);
    _model->setHeaderData(idName, Qt::Horizontal, tr("Name"));
    int idDescr = _model->fieldIndex(PackageTable::fieldDescr);
    _model->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));
*/
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
//    _ui->listPackages->setColumnHidden(0, true);
//    _ui->listPackages->resizeColumnToContents(2);

//    connect(_ui->listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

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


