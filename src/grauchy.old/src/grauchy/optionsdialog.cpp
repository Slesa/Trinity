#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "optionspage.h"
#include "settingspage.h"
#include "packagespage.h"
#include "resources.h"
#include <QPushButton>

OptionsDialog::OptionsDialog(QWidget *parent) :
    FloatingDialog(parent),
    ui(new Ui::OptionsDialog)
{
    this->setWindowIcon(Resources::iconOptions());
    ui->setupUi(this);

    while(ui->stackedPages->count()) ui->stackedPages->removeWidget(ui->stackedPages->widget(0));

    connect(ui->listContent, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    createPages();
    ui->listContent->setCurrentRow(0);
    ui->buttonBox->button(QDialogButtonBox::Close)->setIcon(Resources::iconClose());
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
    PackagesPage* packagesPage = new PackagesPage(this);
    createItem(packagesPage);
    ui->stackedPages->addWidget(packagesPage);

    OptionsPage* settingsPage = new SettingsPage(this);
    createItem(settingsPage);
    ui->stackedPages->addWidget(settingsPage);
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
