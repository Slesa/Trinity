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
    HotkeyDialog(QSqlRelationalTableModel* hotkeyModel, QWidget *parent = 0);
    ~HotkeyDialog();

    Hotkey getData();
    void setData(const Hotkey& hotkey);

signals:
    void takeData(HotkeyDialog* dlg);

protected:
    virtual void accept();

private slots:
    void onKeyStrokes();

private:
    Ui::HotkeyDialog *ui;
    QSqlRelationalTableModel* _hotkeyModel;
};

#endif // HOTKEYDIALOG_H
