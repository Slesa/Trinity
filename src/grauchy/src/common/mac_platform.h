#ifndef MAC_PLATFORM_H
#define MAC_PLATFORM_H

#include "platform_base.h"

class MacPlatform :  public PlatformBase
{
    Q_OBJECT

public:
    MacPlatform(int & argc, char** argv);
    virtual QKeySequence getHotkey() const
    {
        return oldKey;
    }
    virtual bool setHotkey(const QKeySequence& newHotkey, QObject* receiver, const char* slot);

private:
    QKeySequence oldKey;
};

#endif

