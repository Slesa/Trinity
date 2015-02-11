#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include "data/package.h"
#include <QDialog>
#include <QModelIndex>

namespace Ui {
class PackageDialog;
}

class HotkeyDialog;
class QSqlRelationalTableModel;

class PackageDialog : public QDialog
{
    Q_OBJECT

public:
    PackageDialog(QSqlRelationalTableModel* model, QWidget *parent = 0);
    ~PackageDialog();

    void setData(QModelIndex index);
signals:
    void closeMe(QDialog* dlg);

protected:
    virtual void accept();
    virtual void done(int r);

private slots:
    void onAddHotkey();
    void onEditHotkey();
//    void onEditHotkey(QListWidgetItem* item);
    void onTakeHotkey(HotkeyDialog* dlg);
    void onHotkeyClosed(QDialog* dlg);

private:
    void openDialog(QDialog* dlg);

private:
    Ui::PackageDialog* _ui;
    QList<QDialog*> _openDialogs;
    QSqlRelationalTableModel* _model;
    QModelIndex _editIndex;
};

#endif // PACKAGEDIALOG_H
