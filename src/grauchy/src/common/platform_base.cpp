#include "platform_base.h"

PlatformBase::PlatformBase(int& argc, char** argv)
    : QApplication(argc, argv)
{
    // @@@ platform = this;
}
