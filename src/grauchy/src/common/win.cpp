#include "win_platform.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
    return new WinPlatform(argc, argv);
}
