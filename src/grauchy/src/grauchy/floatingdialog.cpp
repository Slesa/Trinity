#include "floatingdialog.h"

FloatingDialog::FloatingDialog(QWidget* parent)
    : QDialog(parent)
{

}

void FloatingDialog::done(int r)
{
    QDialog::done(r);
    emit closeMe(this);
}
