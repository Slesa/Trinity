#include "settingspage.h"
#include "ui_settingspage.h"

SettingsPage::SettingsPage(QWidget *parent)
    : OptionsPage(parent)
    , ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

QIcon SettingsPage::getIcon()
{
    return QIcon(":/resources/settings.png");
}

QString SettingsPage::getTitle()
{
    return tr("Settings");
}
