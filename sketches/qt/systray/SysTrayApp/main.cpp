#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QSystemTrayIcon>
#include "window.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);

    QApplication a(argc, argv);

    if(!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("SysTray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    Window w;
    w.show();
    return a.exec();
}
