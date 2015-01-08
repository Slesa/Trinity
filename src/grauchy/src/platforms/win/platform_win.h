#ifndef PLATFORM_WIN
#define PLATFORM_WIN

#include "platform_base.h"

class PlatformWin :  public PlatformBase
{
    Q_OBJECT

public:
    PlatformWin(int & argc, char** argv);

};

#endif

