#include "bookwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BookWindow win;
    win.show();

    return app.exec();
}
