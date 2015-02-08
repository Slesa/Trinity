#ifndef PACKAGE_H
#define PACKAGE_H

#include "hotkey.h"
#include "entity.h"
#include <QString>

/*
 * A package consist of a name and the list of its hotkeys, e.g. "VI" and all known shortcuts for it.
 */
class Package : public Entity
{
public:
    Package();

    QString getName() { return _name; }
    void setName(const QString& name) { _name = name; }

    QString getDescription() { return _description; }
    void setDescription(const QString& description) { _description = description; }

    QList<Hotkey> getHotkeys() const { return _hotkeys; }

private:
    QString _name;
    QString _description;
    QList<Hotkey> _hotkeys;
};

#endif // PACKAGE_H
