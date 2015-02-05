#ifndef PACKAGEDIALOG_H
#define PACKAGEDIALOG_H

#include <QDialog>

namespace Ui {
class PackageDialog;
}

class HotkeyDialog;

class PackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageDialog(QWidget *parent = 0);
    ~PackageDialog();

protected:
    virtual void done(int r);

private slots:
    void onAddHotkey();
    void onEditHotkey();
    void onTakeHotkey(HotkeyDialog* dlg);
    void onHotkeyClosed(QDialog* dlg);

private:
    void openDialog(QDialog* dlg);

private:
    Ui::PackageDialog *ui;
    QList<QDialog*> _openDialogs;
};

#endif // PACKAGEDIALOG_H
