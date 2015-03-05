#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include "data/package.h"
#include "floatingdialog.h"
#include <QModelIndex>

namespace Ui {
class PackageDialog;
}

class HotkeyDialog;
class QSqlRelationalTableModel;

class PackageDialog : public FloatingDialog
{
    Q_OBJECT

public:
    PackageDialog(QSqlRelationalTableModel* model, QWidget *parent = 0);
    ~PackageDialog();

    void setData(QModelIndex index);

protected:
    virtual void accept();
//    virtual void done(int r);

private slots:
    void onHotkeyAdd();
    void onHotkeyEdit();
    void onHotkeyEdit(QModelIndex index);
    void onHotkeyRemove();

//    void onTakeHotkey(HotkeyDialog* dlg);
//    void onHotkeyClosed(QDialog* dlg);

    void onCurrentRowChanged(QModelIndex index);
    void updateHeader(QModelIndex, int, int);

    void gotChanges();
private:
    void noChanges();
//    void openDialog(QDialog* dlg);
    void createHotkeyModel();

private:
    Ui::PackageDialog* _ui;
    QList<QDialog*> _openDialogs;
    QSqlRelationalTableModel* _model;
    QSqlRelationalTableModel* _hotkeyModel;
    int _editIndex;
};

#endif // PACKAGEDIALOG_H
