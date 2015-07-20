#include "keystrokedialog.h"
#include "ui_keystrokedialog.h"
#include "resources.h"
#include <QPushButton>

KeyStrokeDialog::KeyStrokeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyStrokeDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setIcon(Resources::iconOk());
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setIcon(Resources::iconCancel());
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
