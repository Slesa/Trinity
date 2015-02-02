#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void onOptions();
    void onQuit();

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
