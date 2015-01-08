#ifndef PLATFORM_MAC
#define PLATFORM_MAC

#include "platform_base.h"

class PlatformMac :  public PlatformBase
{
    Q_OBJECT

public:
    PlatformMac(int & argc, char** argv);

};

#endif

