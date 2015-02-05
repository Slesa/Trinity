#ifndef PACKAGE_H
#define PACKAGE_H

#include "hotkey.h"
#include <QString>

/*
 * A package consist of a name and the list of its hotkeys, e.g. "VI" and all known shortcuts for it.
 */
class Package
{
public:
    Package();

    QString getName() { return _name; }
    void setName(const QString& name) { _name = name; }

    QList<Hotkey> getHotkeys() const { return _hotkeys; }

private:
    QString _name;
    QList<Hotkey> _hotkeys;
};

#endif // PACKAGE_H
