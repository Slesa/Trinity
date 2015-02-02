#include "mac_platform.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
    return new MacPlatform(argc, argv);
}
