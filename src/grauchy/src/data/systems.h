#ifndef OPERATINGSYSTEMS
#define OPERATINGSYSTEMS

#include <QFlags>

/*
 * Declare all available operating systems
 */
enum SystemFlag
{
    SystemWindows,
    SystemLinux,
    SystemMac
};

Q_DECLARE_FLAGS(SystemFlags, SystemFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(SystemFlags)

#endif // OPERATINGSYSTEMS

