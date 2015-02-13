#ifndef HOTKEYDIALOG_H
#define HOTKEYDIALOG_H

#include "data/hotkey.h"
#include "floatingdialog.h"
#include <QDialog>
#include <QModelIndex>

namespace Ui {
class HotkeyDialog;
}

class QSqlRelationalTableModel;

class HotkeyDialog : public FloatingDialog
{
    Q_OBJECT

public:
    HotkeyDialog(int package, QSqlRelationalTableModel* hotkeyModel, QWidget *parent = 0);
    ~HotkeyDialog();

    void setData(QModelIndex index);

signals:
    void takeData(HotkeyDialog* dlg);

protected:
    virtual void accept();

private slots:
    void onKeyStrokes();

private:
    Ui::HotkeyDialog *ui;
    QSqlRelationalTableModel* _hotkeyModel;
    int _package;
    int _editIndex;
};

#endif // HOTKEYDIALOG_H
