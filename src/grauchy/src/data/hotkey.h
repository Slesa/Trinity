#ifndef HOTKEY_H
#define HOTKEY_H

#include "entity.h"
#include <QString>

class Hotkey : public Entity
{
public:
    static const int AllSystems = 31;

public:
    Hotkey();

    // The package this hotkey belongs to
    int getPackage() { return _package; }
    void setPackage(int package) { _package = package; }

    // A short descitpion of the hotkey
    QString getDescription() const { return _description; }
    void setDescription(const QString& description) { _description = description; }

private:
    int _package;
    QString _description;
};

#endif // HOTKEY_H
