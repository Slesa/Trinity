#include "bookwindow.h"
#include "ui_bookwindow.h"
#include "initdb.h"
#include <QtSql/QtSql>

BookWindow::BookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookWindow)
{
    ui->setupUi(this);

    if(!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, tr("Unable to load database"), tr("QSQLITE drive is needed to run."));

    QSqlError error = initDb();
    if(error.type()!=QSqlError::NoError) {
        showError(error);
        return;
    }

    model = new QSqlRelationalTableModel(ui->bookTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("books");

    authorIdx = model->fieldIndex("author");
    genreIdx = model->fieldIndex("genre");


}

BookWindow::~BookWindow()
{
    delete ui;
}

void BookWindow::showError(const QSqlError &error)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + error.text());
}
