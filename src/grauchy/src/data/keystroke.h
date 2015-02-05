#ifndef KEYSTROKE_H
#define KEYSTROKE_H

#include "modifiers.h"
#include <QChar>

/*
 * A keystoke collects one character with the additionally pressed modifier keys
 */
class KeyStroke
{
public:
    KeyStroke();

    QChar getKey() { return _key; }
    void setKey(const QChar& key) { _key = key; }

    ModifierFlags getModifiers() { return _modifiers; }
    void setModifiers(ModifierFlags modifiers) { _modifiers = modifiers; }

private:
    QChar _key;
    ModifierFlags _modifiers;
};

#endif // KEYSTROKE_H
