#include "platform_unix.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
	return new PlatformUnix(argc, argv);
}