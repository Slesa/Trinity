#include "keystrokedialog.h"
#include "ui_keystrokedialog.h"

KeyStrokeDialog::KeyStrokeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyStrokeDialog)
{
    ui->setupUi(this);
}

KeyStrokeDialog::~KeyStrokeDialog()
{
    delete ui;
}

QString KeyStrokeDialog::getKeyStrokes() const
{
    QKeySequence seq = ui->keyEdit->keySequence();
    return seq.toString();
}
