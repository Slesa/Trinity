#ifndef OPERATINGSYSTEMS
#define OPERATINGSYSTEMS

#include <QFlags>

/*
 * Declare all available operating systems
 */
enum SystemFlag
{
    SystemWindows = 1,
    SystemLinux = 2,
    SystemMac = 4
};

Q_DECLARE_FLAGS(SystemFlags, SystemFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(SystemFlags)

#endif // OPERATINGSYSTEMS

