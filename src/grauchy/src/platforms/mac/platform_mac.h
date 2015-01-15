#ifndef PLATFORM_MAC
#define PLATFORM_MAC

#include "platform_base.h"

class PlatformMac :  public PlatformBase
{
    Q_OBJECT

public:
    PlatformMac(int & argc, char** argv);
    virtual QKeySequence getHotkey() const
    {
        return oldKey;
    }
    virtual bool setHotkey(const QKeySequence& newHotkey, QObject* receiver, const char* slot);

private:
    QKeySequence oldKey;
};

#endif

