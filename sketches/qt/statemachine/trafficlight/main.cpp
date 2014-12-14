#include <QtWidgets>
#include "lightwidget.h"
#include "trafficlight.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TrafficLight widget;
    widget.resize(110, 300);
    widget.show();

    return a.exec();
}
