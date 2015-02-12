#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "floatingdialog.h"

namespace Ui {
class OptionsDialog;
}

class QListWidgetItem;
class OptionsPage;


class OptionsDialog : public FloatingDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

public slots:
    void changePage(QListWidgetItem*,QListWidgetItem*);

private:
    void createPages();
    QListWidgetItem* createItem(OptionsPage* page);

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
