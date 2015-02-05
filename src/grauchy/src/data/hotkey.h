#ifndef HOTKEY_H
#define HOTKEY_H

#include "systems.h"
#include "modifiers.h"
#include "keystroke.h"
#include <QString>
#include <QStringList>

/*
 * A hotkey combines a list of keystrokes with a description and a few tags to allow a better search result.
 */
class Hotkey
{
public:
    Hotkey();

    // A short descitpion of the hotkey
    QString getDescription() const { return _description; }
    void setDescription(const QString& description) { _description = description; }

    // A list of tags to search for
    QStringList getTags() const { return _tags; }
    void setTags(const QStringList& tags) { _tags = tags; }

    // On which operating system this hotkey is available on?
    SystemFlags getSystems() const { return _systems; }
    void setSystems(SystemFlags systems) { _systems = systems; }

    // Get the list of keystrokes to perform the action
    QList<KeyStroke> getKeyStrokes() { return _keyStrokes; }
    void setKeyStrokes(const QList<KeyStroke> keyStrokes) { _keyStrokes = keyStrokes; }

private:
    QString _description;
    QStringList _tags;
    SystemFlags _systems;
    QList<KeyStroke> _keyStrokes;
};

#endif // HOTKEY_H
