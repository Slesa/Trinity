#ifndef MODIFIER
#define MODIFIER

#include <QFlags>

/*
 * Declare all available modifier keys on a keyboard
 */
enum Modifiers
{
    Shift,
    Control,
    Alt,
    Meta
};

Q_DECLARE_FLAGS(ModifierFlags, Modifiers)
Q_DECLARE_OPERATORS_FOR_FLAGS(ModifierFlags)

#endif // MODIFIER

