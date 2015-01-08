#include "platform_mac.h"
#include <QApplication>

QApplication* createApplication(int& argc, char** argv)
{
	return new PlatformMac(argc, argv);
}