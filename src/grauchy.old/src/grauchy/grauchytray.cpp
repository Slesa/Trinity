#include "grauchytray.h"
#include "grauchywidget.h"
#include <QAction>
#include <QKeySequence>
#include <QMenu>
#include <QDebug>

GrauchyTray::GrauchyTray(GrauchyWidget* parent)
    : _parent(parent)
{

}

void GrauchyTray::showTrayIcon()
{
    if(!QSystemTrayIcon::isSystemTrayAvailable())
    {
        qWarning() << "No system tray available";
        return;
    }

    if( !_trayIcon )
    {
        _trayIcon = createTrayIcon();
    }

    _trayIcon->show();
}

QSystemTrayIcon* GrauchyTray::createTrayIcon()
{
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);

    QKeySequence hotkey;
    trayIcon->setToolTip(tr("Grauchy (press %1 to activate)").arg(hotkey.toString()));
    trayIcon->setIcon(QIcon(":/resources/grauchy24.png"));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    QMenu* trayMenu = new QMenu(_parent);
    trayMenu->addAction(actShow);
    trayMenu->addAction(actOptions);
    trayMenu->addSeparator();
    trayMenu->addAction(actExit);
    trayIcon->setContextMenu(trayMenu);

    return trayIcon;
}

void GrauchyTray::createActions()
{
    actShow = new QAction(tr("Show Grauchy"), this);
    connect(actShow, SIGNAL(triggered()), this, SLOT(showLaunchy()));

    actReloadSkin = new QAction(tr("Reload skin"), this);
    actReloadSkin->setShortcut(QKeySequence(Qt::Key_F5 | Qt::SHIFT));
    connect(actReloadSkin, SIGNAL(triggered()), this, SLOT(reloadSkin()));
    addAction(actReloadSkin);

    actOptions = new QAction(tr("Options"), this);
    actOptions->setShortcut(QKeySequence(Qt::Key_Comma | Qt::CTRL));
    connect(actOptions, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
    addAction(actOptions);

    actExit = new QAction(tr("Exit"), this);
    actExit->setShortcut(QKeySequence(Qt::Key_X | Qt::CTRL));
    connect(actExit, SIGNAL(triggered()), this, SLOT(close()));
}
