#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "optionspage.h"
#include "settingspage.h"
#include "packagespage.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    while(ui->stackedPages->count()) ui->stackedPages->removeWidget(ui->stackedPages->widget(0));

    connect(ui->listContent, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    createPages();
    ui->listContent->setCurrentRow(0);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::changePage(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(!current)
        current = previous;
    ui->stackedPages->setCurrentIndex(ui->listContent->row(current));
}

void OptionsDialog::createPages()
{
    OptionsPage* settingsPage = new SettingsPage(this);
    createItem(settingsPage);
    ui->stackedPages->addWidget(settingsPage);

    PackagesPage* packagesPage = new PackagesPage(this);
    createItem(packagesPage);
    ui->stackedPages->addWidget(packagesPage);
}

QListWidgetItem* OptionsDialog::createItem(OptionsPage* page)
{
    QListWidgetItem* item = new QListWidgetItem(ui->listContent);
    item->setIcon(page->getIcon());
    item->setText(page->getTitle());
    item->setTextAlignment(Qt::AlignHCenter);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    return item;
}
