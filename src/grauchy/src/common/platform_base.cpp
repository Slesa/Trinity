#include "platform_base.h"
#include <QFileIconProvider>

PlatformBase::PlatformBase(int& argc, char** argv)
: QApplication(argc, argv)
{
    // @@@ platform = this;
}

PlatformBase::~PlatformBase()
{
    if (_icons)
    {
        delete _icons;
        _icons = NULL;
    }
}
