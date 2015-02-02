#ifndef WIN_PLATFORM_H
#define WIN_PLATFORM_H

#include "platform_base.h"

class WinPlatform :  public PlatformBase
{
    Q_OBJECT

public:
    WinPlatform(int & argc, char** argv);

};

#endif

