#include "platform_base.h"
#include "globals.h"
#include <QFileIconProvider>

PlatformBase::PlatformBase(int& argc, char** argv)
: QApplication(argc, argv)
{
    g_platform = this;
}

PlatformBase::~PlatformBase()
{
}
