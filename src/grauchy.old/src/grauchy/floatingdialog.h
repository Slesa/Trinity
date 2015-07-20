#ifndef FLOATINGDIALOG_H
#define FLOATINGDIALOG_H

#include <QDialog>

class FloatingDialog : public QDialog
{
    Q_OBJECT

public:
    FloatingDialog(QWidget* parent=NULL);

signals:
    void closeMe(QDialog* dlg);

protected:
    virtual void done(int r);
};

#endif // FLOATINGDIALOG_H
