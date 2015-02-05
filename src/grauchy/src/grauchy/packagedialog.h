#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include "data/package.h"
#include <QDialog>

namespace Ui {
class PackageDialog;
}

class HotkeyDialog;

class PackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageDialog(const Package& package, QWidget *parent = 0);
    ~PackageDialog();

    Package getData();
    void setData(const Package& package);

signals:
    void closeMe(QDialog* dlg);
    void takeData(PackageDialog* dlg);

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
    Ui::PackageDialog *ui;
    QList<QDialog*> _openDialogs;
};

#endif // PACKAGEDIALOG_H
