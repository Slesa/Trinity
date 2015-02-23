#ifndef KEYSTROKE_H
#define KEYSTROKE_H

#include "entity.h"
#include "systems.h"
#include <QString>

/*
 * A keystoke collects one character with the additionally pressed modifier keys
 */
class KeyStroke : public Entity
{
public:
    KeyStroke();

    int getHotkey() const { return _hotkey; }
    void setHotkey(int hotkey) { _hotkey = hotkey; }

    QString getSequence() { return _sequence; }
    void setSequence(const QString& sequence) { _sequence = sequence; }

    // On which operating system this hotkey is available on?
    int getSystem() const { return _system; }
    void setSystem(int system) { _system = (SystemFlag)system; }

private:
    int _hotkey;
    QString _sequence;
    SystemFlag _system;
};

#endif // KEYSTROKE_H
