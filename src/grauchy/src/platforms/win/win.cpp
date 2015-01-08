#include "platform_win.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
	return new PlatformWin(argc, argv);
}