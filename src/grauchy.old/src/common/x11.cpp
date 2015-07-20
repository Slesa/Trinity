#include "x11_platform.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
    return new X11Platform(argc, argv);
}
