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
    virtual void done(int r);

private slots:
    void onAddHotkey();
    void onEditHotkey();
//    void onEditHotkey(QListWidgetItem* item);
    void onTakeHotkey(HotkeyDialog* dlg);
    void onHotkeyClosed(QDialog* dlg);

    void updateHeader(QModelIndex, int, int);

private:
    void openDialog(QDialog* dlg);
    void createHotkeyModel();

private:
    Ui::PackageDialog* _ui;
    QList<QDialog*> _openDialogs;
    QSqlRelationalTableModel* _model;
    QSqlRelationalTableModel* _hotkeyModel;
    int _editIndex;
};

#endif // PACKAGEDIALOG_H
