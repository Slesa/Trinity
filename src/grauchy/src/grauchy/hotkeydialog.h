#ifndef HOTKEYDIALOG_H
#define HOTKEYDIALOG_H

#include "data/hotkey.h"
#include <QDialog>

namespace Ui {
class HotkeyDialog;
}

class HotkeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HotkeyDialog(QWidget *parent = 0);
    ~HotkeyDialog();

    Hotkey getData();
    void setData(const Hotkey& hotkey);

signals:
    void closeMe(QDialog* dlg);
    void takeData(HotkeyDialog* dlg);

protected:
    virtual void accept();
    virtual void done(int r);

private slots:
    void onKeyStrokes();

private:
    Ui::HotkeyDialog *ui;
};

#endif // HOTKEYDIALOG_H
