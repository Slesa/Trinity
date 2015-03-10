#ifndef RESOURCES_H
#define RESOURCES_H

#include <QIcon>

class Resources
{
public:
    // Options
    static QIcon iconOptions();

    // A package
    static QIcon iconPackage();
    // A hotkey
    static QIcon iconHotkey();

    // Button OK
    static QIcon iconOk();
    // Button Cancel
    static QIcon iconCancel();
    // Buton Close
    static QIcon iconClose();

    // OS Windows
    static QIcon iconWindows();
    // OS Linux
    static QIcon iconLinux();
    // OS Mac
    static QIcon iconMac();

    static QIcon iconGeneral();
};

#endif // RESOURCES_H

