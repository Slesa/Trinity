#include "mainview.h"
#include "ui_mainview.h"
#include "optionsdialog.h"
#include "persist/persist.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
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
    createModel();

    connect(_ui->_pushQuit, SIGNAL(clicked()), SLOT(onQuit()));
    connect(_ui->_pushOptions, SIGNAL(clicked()), SLOT(onOptions()));
}

MainView::~MainView()
{
    if(_optionsDlg) delete _optionsDlg;
    delete _model;
    delete _persist;
    delete _ui;
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
    _model->select();
    _ui->_comboPackages->setCurrentIndex(0);
}

void MainView::closeOptions()
{
    _optionsDlg = NULL;
    updateData();
}

void MainView::createModel()
{
    _model = new QSqlRelationalTableModel(_ui->_comboPackages);
    _model->setTable(PackageTable::tableName);
/*
    int idIndex = _model->fieldIndex(PackageTable::fieldId);
    _model->setHeaderData(idIndex, Qt::Horizontal, tr("Id"));
    int idName = _model->fieldIndex(PackageTable::fieldName);
    _model->setHeaderData(idName, Qt::Horizontal, tr("Name"));
    int idDescr = _model->fieldIndex(PackageTable::fieldDescr);
    _model->setHeaderData(idDescr, Qt::Horizontal, tr("Description"));
*/
    if(!_model->select())
    {
        showError(_model->lastError());
        return;
    }
    if(!_model->rowCount())
    {
        PackageTable packageTable;
        QSqlQuery query = packageTable.prepareInsertion();
        int zshIdx = packageTable.addPackage(query, "Zsh", "The glorious shell").toInt();
        int viIdx = packageTable.addPackage(query, "Vi", "The best editor").toInt();

        HotkeyTable hotkeyTable;
        query = hotkeyTable.prepareInsertion();
        hotkeyTable.addHotkey(query, zshIdx, "Goto start of line", Hotkey::AllSystems);
        hotkeyTable.addHotkey(query, zshIdx, "Goto end of line", Hotkey::AllSystems);
        hotkeyTable.addHotkey(query, viIdx, "Goto start of line", Hotkey::AllSystems);
        hotkeyTable.addHotkey(query, viIdx, "Goto end of line", Hotkey::AllSystems);
    }

    _ui->_comboPackages->setModel(_model);
    _ui->_comboPackages->setModelColumn(1);
//    _ui->listPackages->setColumnHidden(0, true);
//    _ui->listPackages->resizeColumnToContents(2);

//    connect(_ui->listPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex)));

    updateData();
}

void MainView::showError(const QSqlError& error)
{
    QMessageBox::critical(this, tr("Unable to initialize database"),
                          tr("Error initializing datase: ")+error.text());
}


