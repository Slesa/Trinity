#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include "optionspage.h"

namespace Ui {
class SettingsPage;
}

class SettingsPage : public OptionsPage
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = 0);
    ~SettingsPage();

    QIcon getIcon();
    QString getTitle();

private:
    Ui::SettingsPage *ui;
};

#endif // SETTINGSPAGE_H
