#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE
class ArrowPad;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    ArrowPad* arrowPad;
    QMenu* fileMenu;
    QAction* exitAction;
};

#endif // MAINWINDOW_H
