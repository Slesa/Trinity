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
class QLineEdit;
class QString;
class KeyStrokeTable;

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
    void onAllSequence();
    void onWinSequence();
    void onLinSequence();
    void onMacSequence();

    void gotChanges();
private:
    void noChanges();
    void onSequence(QLineEdit*);

private:
    Ui::HotkeyDialog* _ui;
    QSqlRelationalTableModel* _hotkeyModel;
    QSqlRelationalTableModel* _keyStrokeModel;
    int _packageId;
    int _editedHotkeyId;
};

#endif // HOTKEYDIALOG_H
