#ifndef GRAUCHYTRAY_H
#define GRAUCHYTRAY_H

#include <QSystemTrayIcon>

class GrauchyWidget;
class QAction;

class GrauchyTray : public QObject
{
public:
    GrauchyTray(GrauchyWidget* parent);
	void showTrayIcon();

public slots:
	void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon* createTrayIcon();
    void createActions();
private:
    GrauchyWidget* _parent;
    QSystemTrayIcon* _trayIcon;
    QAction* actShow;
    QAction* actReloadSkin;
    QAction* actOptions;
    QAction* actExit;};

#endif // GRAUCHYTRAY_H
