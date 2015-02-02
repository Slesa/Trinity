#include "mainview.h"
#include "ui_mainview.h"
#include "optionsdialog.h"
#include <QApplication>

// http://www.bogotobogo.com/Qt/Qt5_QListView_QStringListModel_ModelView_MVC.php

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    connect(ui->_pushQuit, SIGNAL(clicked()), SLOT(onQuit()));
    connect(ui->_pushOptions, SIGNAL(clicked()), SLOT(onOptions()));
}

MainView::~MainView()
{
    delete ui;
}

void MainView::onOptions()
{
    OptionsDialog* dlg = new OptionsDialog(this);
    dlg->show();
}

void MainView::onQuit()
{
    qApp->quit();
}
